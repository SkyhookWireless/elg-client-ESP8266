#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "FS.h"
#include <ArduinoJson.h>

// TODO: Allow the user to specify to restart in AP mode or Client Mode after AP change

// provide text for the WiFi status
const char *str_status[]= {
    "WL_IDLE_STATUS",
    "WL_NO_SSID_AVAIL",
    "WL_SCAN_COMPLETED",
    "WL_CONNECTED",
    "WL_CONNECT_FAILED",
    "WL_CONNECTION_LOST",
    "WL_DISCONNECTED"
};

// Class allows WiFi to connect and check for connection 
// status while also handling interrupts
class WiFiWrapper{
    // denotes if WiFi is currently connected
    // last updated
    unsigned long previousMillis;
    int check_times;
    bool init_check_finish;
    
  public:
  WiFiWrapper(){
    check_times = 0;
    bool init_check_finish = false;
  }
  
  bool get_init_check_finish(){
    return init_check_finish;
  }

  // run this function and then run init_check_connection
  void connect_to(String ssid, String password){
    WiFi.begin(ssid.c_str(),password.c_str());
    init_check_finish = false;
    previousMillis = 0;
    check_times = 0;
  }
  
  void connection_reset(){
    WiFi.disconnect();
    check_times = 0;
    init_check_finish = false;
  }

  // wifimulti.run() for startup
  bool check_connection(){
    int n = WiFi.status();
    // check if the WiFi is connected
    if(n == WL_CONNECTED){
      return true;
    }
    else{
      return false;
    }
  }

  void init_check_connection(unsigned long interval){
    unsigned long currentMillis = millis();
      // if it is time to update
      if(currentMillis - previousMillis > interval){
        Serial.println("Checking Connection Status");
        
        // check if the WiFi is connected
        int n = WiFi.status();
        switch(n){
          case WL_NO_SSID_AVAIL:
            init_check_finish = true;
            break;
          case WL_CONNECTED:
            init_check_finish = true;
            break;
          case WL_CONNECT_FAILED:
            init_check_finish = true;
            break;
          default:
            check_times++;
            break;
        }
        Serial.println(str_status[n]);

        // update the time
        previousMillis = currentMillis;
    }
  }
};

/* Set these to your desired credentials. */
const char *ssid = "ELG-Client";
const char *password = "";

ESP8266WebServer server(80);
WiFiWrapper main_wifi;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

void setup() {
  SPIFFS.begin();
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.mode(WIFI_AP_STA);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  WiFi.softAPmacAddress(mac);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  // TODO: make a routes page that handles this for us
  server.on("/", handleRoot);
  server.on("/jquery.js", HTTP_GET, handleResources);
  server.on("/skyhookclient/scan", HTTP_GET, handleScan);
  server.on("/bootstrap.min.css", HTTP_GET, handleResources);
  server.on("/bootstrap.min.js", HTTP_GET, handleResources);
  server.on("/skyhookclient/changeap", HTTP_POST, handleChangeAP);
  server.onNotFound(handleNotFound);
//  server.on("/skyhookclient/getlocation", HTTP_GET, getLocation);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // we will have a state here that will keep track of AP-Mode vs Client-Mode
  //if(state == AP){
    server.handleClient();
  //}
  //else{
  //  
  //}
}

void handleRoot() {
  // TODO scan surrounding networks
  // TODO: Server send general HTML with requests for scan list instead of waiting for the scan
  String connection = "";
  if(WiFi.SSID() != NULL && WiFi.status() == WL_CONNECTED){
    connection = "Connected To: " + WiFi.SSID();
  }
  else{
    connection = "Not connected :(";
  }
  server.send(200, "text/html", "<head><link rel=\"stylesheet\" href=\"/bootstrap.min.css\"></link><script src=\"jquery.js\"></script></link><script src=\"bootstrap.min.js\"></script></head><h1>"+connection+"</h1><form action=\"/skyhookclient/changeap\" method=\"post\"><input type=\"text\" name=\"ssid\"><input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Submit\"></form>");
}

void handleResources(){
  // begin file mangament
  
  Serial.println("Requesting " + server.uri());

  File f;
  if(SPIFFS.exists(server.uri())){
    f = SPIFFS.open(server.uri(), "r");
    if(!f){
      Serial.println(server.uri() + " does not exist");
    }
    if(server.streamFile(f, getDataType(server.uri())) != f.size()){
      Serial.println("Error");
    }
    f.close();
  }
  else{
    server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
  }
}

// Returns a JSON of scanned networks
void handleScan(){
  Serial.println("Scanning Networks");
  int n = WiFi.scanNetworks();
  DynamicJsonBuffer scan_obj_buf;
  JsonObject& scan_obj = scan_obj_buf.createObject();
  
  for (int i = 0; i < n; i++){
    DynamicJsonBuffer scan_info_buf;
    JsonObject& scan_info = scan_obj.createNestedObject(WiFi.BSSIDstr(i));
    scan_info["ssid"]=WiFi.SSID(i);
    scan_info["channel"] = WiFi.channel(i);
    scan_info["rssi"] = WiFi.RSSI(i);
    scan_info["encrypt"] = encryptionTypeStr(WiFi.encryptionType(i));
  }
  scan_obj.prettyPrintTo(Serial);
    size_t len = scan_obj.measurePrettyLength();
  char* responseJSON = (char*)malloc(scan_obj.measurePrettyLength() * sizeof(char));
  scan_obj.prettyPrintTo(responseJSON, scan_obj.measurePrettyLength());
  server.send(200,"application/json",responseJSON);
}
// TODO: on client side, notify them that changing AP will disconnect them
void handleChangeAP(){
  Serial.println("User is trying to change AP");
  if(server.hasArg("ssid") && server.hasArg("password")){
    Serial.println("SSID: " + server.arg("ssid"));
    Serial.println("Password: " + server.arg("password")); 
    // server.send(200, "text/html", "<head></head><h1>Attemping to connect to SSID "+server.arg("ssid")+". AP will now shut down"+"</h1>");
  }
  
  // TODO: Tell user that the client will now disconnect and attempt to connect to the AP
  // server send: restarting page
  // OLED: Attempting to connect to SSID

  //WIFI.begin() will move the AP channel 
  main_wifi.connect_to(server.arg("ssid"), server.arg("pw"));
  Serial.println("Current connection status: " + String(main_wifi.get_init_check_finish()));
  while(!main_wifi.get_init_check_finish() && !main_wifi.check_connection()){
    main_wifi.init_check_connection(500);
    delay(1);
    // Serial.println("Checking for interrupts");
    // Run Interrupt Class
  }
  Serial.println("Finished Checking for Wifi Connection");
  if(main_wifi.check_connection()){
    Serial.println("Connected to WiFi");
    if(save_connected_network(server.arg("password"))){
      print_saved_networks();
      server.send(200,"text/html", "<head></head><h1>AP connected and saved</h1>");
    }
    // Send as internval service error if AP can't be saved
    else{
      Serial.println("Couldn't save AP to database");
      //server.send(500,"text/html", "<head></head><h1>Couldn't save AP to database</h1>");
    }
  }
  // Device couldn't connect to AP 
  else{
    Serial.println("Failed to Connect");
    //server.send(500, "text/html", "<head></head><h1>Failed to Connect</h1>");
  }
}

void print_saved_networks(){
  char APjson[417];
  if(SPIFFS.exists("/AP.json")){
    File a = SPIFFS.open("/AP.json","r");
    a.readBytesUntil(0,APjson,417);
    a.close();
  }
  DynamicJsonBuffer bssid_obj_buf;
  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);
  bssid_obj.prettyPrintTo(Serial);
}

// Function will save the connected network into JSON formated file
// TODO: Impose number of saved networks (currently magic numbers are
// configured to three bssids
bool save_connected_network(String password){
  // TODO: make configue file for magic numbers
  // 417 Because of max ssid and password calculation (will document)
  char APjson[417];
  String bssid = WiFi.BSSIDstr();
  Serial.println(bssid);
  // write existing data to a buffer
  if(SPIFFS.exists("/AP.json")){
    File a = SPIFFS.open("/AP.json","r");
    a.readBytesUntil(0,APjson,417);
    a.close();
  }
  // if ssid/pw storage doesn't exist, make an empty json array
  else{
    APjson[0] = '{';
    APjson[1] = '}';
  }

  // dynamic buffers (should only be used for devices with larger RAM)
  DynamicJsonBuffer bssid_obj_buf;
  DynamicJsonBuffer bssid_info_buf;

  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);
  
  // if the BSSID already exists we will update it by removing it and then 
  // readding it (keeping the stack style of BSSID storage)
  if(bssid_obj[bssid] != NULL){
    bssid_obj.remove(bssid);
  }
  JsonObject& bssid_info = bssid_obj.createNestedObject(bssid);
  bssid_info["ssid"] = WiFi.SSID();
  bssid_info["pw"] = password;

  // remove the tmp file check
  if(!SPIFFS.exists("/APtmp.json")){
    SPIFFS.remove("/APtmp.json");
  }
  
  File b = SPIFFS.open("/APtmp.json","w+");
  // ERROR: file couldn't be open or created
  if(!b){
    return 0;
  }
  // write to file
  bssid_obj.printTo(b);
  b.close();

  // delete the old AP list and update the new one to have the same name
  SPIFFS.remove("/AP.json");
  SPIFFS.rename("/APtmp.json", "/AP.json");

  // double checks that the JSON exists
  if(SPIFFS.exists("/AP.json")){
    return 1;
  }
  else{
    return 0;
  }
}

void handleNotFound(){
  server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
}

String getDataType(String path){
  if(path.endsWith(".htm")) return "text/html";
  else if(path.endsWith(".css")) return "text/css";
  else if(path.endsWith(".js")) return "application/javascript";
  else if(path.endsWith(".png")) return "image/png";
  else if(path.endsWith(".gif")) return "image/gif";
  else if(path.endsWith(".jpg")) return "image/jpeg";
  else if(path.endsWith(".ico")) return "image/x-icon";
  else if(path.endsWith(".xml")) return "text/xml";
  else if(path.endsWith(".pdf")) return "application/pdf";
  else if(path.endsWith(".zip")) return "application/zip";
  else return "text/htm";
}

String encryptionTypeStr(uint8_t authmode) {
    switch(authmode) {
        case ENC_TYPE_NONE:
            return "NONE";
        case ENC_TYPE_WEP:
            return "WEP";
        case ENC_TYPE_TKIP:
            return "TKIP";
        case ENC_TYPE_CCMP:
            return "CCMP";
        case ENC_TYPE_AUTO:
            return "AUTO";
        default:
            return "?";
    }
}
