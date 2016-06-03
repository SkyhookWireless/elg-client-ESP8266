#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "FS.h"
#include <ArduinoJson.h>

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

class WiFiWrapper{
    bool connection_status;
    unsigned long previousMillis;
    unsigned long interval;
    int timeout;
    int check_times;
    bool check_finish;
    
  public:
  WiFiWrapper(unsigned long interval_input, int num_timeout){
    connection_status = false;
    interval = interval_input;
    timeout = num_timeout;
    check_times = 0;
    bool check_finish = true;
  }
  bool is_connected(){
    return connection_status;
  }
  bool get_check_finish(){
    return check_finish;
  }
  void connect_to(String ssid, String password){
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid.c_str(),password.c_str());
    check_finish = false;
    connection_status = false;
    previousMillis = 0;
    Serial.println("Attempting to Connect");
  }
  void check_connection(){
    unsigned long currentMillis = millis();
    if(check_times < timeout){
      // if it is time to update
      if(currentMillis - previousMillis > interval){
        Serial.println("Checking Connection Status");
        int n = WiFi.status();
        // check if the WiFi is connected
        if(n == WL_CONNECTED){
          connection_status = true;
          check_finish = true;
          Serial.println("Connected");
        }
        // not yet connected check again later
        else{
          check_times++;
        }
        
        if (n > sizeof(str_status)) Serial.println(n);
        else Serial.println(str_status[n]);

        // update the time
        previousMillis = currentMillis;
      }
    }
  }
};

/* Set these to your desired credentials. */
const char *ssid = "ELG-Client";
const char *password = "";

ESP8266WebServer server(80);
WiFiWrapper main_wifi(500,20);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */

void setup() {
  SPIFFS.begin();
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

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
  server.send(200, "text/html", "<head><link rel=\"stylesheet\" href=\"/bootstrap.min.css\"></link><script src=\"jquery.js\"></script></link><script src=\"bootstrap.min.js\"></script></head><h1>You are connected</h1><form action=\"/skyhookclient/changeap\" method=\"post\"><input type=\"text\" name=\"ssid\"><input type=\"password\" name=\"password\"><br><input type=\"submit\" value=\"Submit\"></form>");
}

void handleResources(){
  // begin file mangament
  
  Serial.println("Requesting " + server.uri());

  File f;
  if(SPIFFS.exists(server.uri()) && !isRestricted(server.uri())){
    f = SPIFFS.open(server.uri(), "r");
    if(server.streamFile(f, getDataType(server.uri())) != f.size()){
      Serial.println("Error");
    }
    f.close();
  }
  else{
    server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
  }
}

void handleScan(){
  server.send(204, "text/html", "<head><head><h1>No Content</h1>");
}

void handleChangeAP(){
  Serial.println("User is trying to change AP");
  if(server.hasArg("ssid") && server.hasArg("password")){
    Serial.println("SSID: " + server.arg("ssid"));
    Serial.println("Password: " + server.arg("password")); 
  }
  
  main_wifi.connect_to(server.arg("ssid"), server.arg("password"));
  Serial.println("Attemtping to Connect");
  Serial.println("Check Finish: " + main_wifi.get_check_finish());
  while(!main_wifi.get_check_finish()){
    main_wifi.check_connection();
    delay(1);
    // Serial.println("Checking for interrupts");
    // Run Interrupt Class
  }
  Serial.println("Finished Checking for Wifi Connection");
  if(main_wifi.is_connected()){
    Serial.println("Connected to WiFi");
    // save_connected_network(WiFi.BSSID(), WiFi.SSID(), server.arg("password"));

  
//
//  object.prettyPrintTo(Serial);

    
  }
  else{
    Serial.println("Failed to Connect");
  }
}

bool save_connected_network(String password){
  // TODO: make configue file for magic numbers
  // 417 Because of max ssid and password calculation (will document)
  char APjson[417];
  char* bssid = (char*)WiFi.BSSID();
  
  // write existing data to a buffer
  if(SPIFFS.exists("/AP.json")){
    File a = SPIFFS.open("/AP.json","r");
    a.readBytesUntil(0,APjson,417);
    a.close();
  }
  // if ssid/pw storage doesn't exist, make an empty json
  else{
    APjson[0] = '{';
    APjson[1] = '}';
  }

  DynamicJsonBuffer bssid_obj_buf;
  DynamicJsonBuffer bssid_info_buf;

  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);
  
  // if the BSSID already exists we will update it by removing it and then readding it (keeping the stack style of BSSID storage)
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
  // write to file
  bssid_obj.printTo(b);
  b.close();

  SPIFFS.remove("/AP.json");
  SPIFFS.rename("/APtmp.json", "/AP.json");

  
  // TODO: error checking not implemented yet
  return 1;
}

void handleNotFound(){
  server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
}

// TODO: Parse a config file on startup in order to make this dynamic 
bool isRestricted(String path){
  if(path=="/pw.txt" || path=="/ssid.txt") return true;
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

String bssidToString( uint8_t *bssid ) {

  char mac[18] = {0};

  sprintf( mac,"%02X:%02X:%02X:%02X:%02X:%02X", bssid[0],  bssid[1],  bssid[2], bssid[3], bssid[4], bssid[5] );
  return String( mac );

}
