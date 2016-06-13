/************************************************
* Authors: Alexander Lin
* 
* Company: Skyhook Wireless
*
************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "FS.h"
#include <ArduinoJson.h>

// for the WiFiWrapper Class for when init_check_connection is called
#define MAX_CHECK_TIMES 30

// TODO: Allow the user to specify to restart in AP mode or Client Mode after AP change

// provide text for the WiFi status
const char *str_status[] = {
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
class WiFiWrapper {
    // denotes if WiFi is currently connected
    unsigned long previousMillis;
    int check_times;
    bool init_check_finish;

  public:
    WiFiWrapper() {
      check_times = 0;
      bool init_check_finish = false;
    }

    // will be set to true when init_check_connect sets the value
    bool get_init_check_finish() {
      return init_check_finish;
    }


    // run this function and then run init_check_connection
    void connect_to(String ssid, String password) {
      WiFi.disconnect();
      delay(5);
      WiFi.begin(ssid.c_str(), password.c_str());

      // resets the check flag
      init_check_finish = false;
      previousMillis = 0;
      check_times = 0;
    }

    void connection_reset() {
      WiFi.disconnect();
      check_times = 0;
      init_check_finish = false;
    }

    // TODO:wifimulti.run() for startup
    // General function to check for connection status
    bool check_connection() {
      int n = WiFi.status();
      // check if the WiFi is connected
      if (n == WL_CONNECTED) {
        return true;
      }
      else {
        return false;
      }
    }

    // meant to be called continuously until init_check_finish is set
    // TODO: something is broken here....
    void init_check_connection(unsigned long interval) {
      unsigned long currentMillis = millis();
      if(!init_check_finish){
        // if it is time to update and under number of times to check
        if (currentMillis - previousMillis > interval && check_times < MAX_CHECK_TIMES) {
          Serial.println("Checking Connection Status");
          Serial.println(check_times);
          // check if the WiFi is connected
          int n = WiFi.status();
          switch (n) {
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
        else if(check_times >= MAX_CHECK_TIMES){
          init_check_finish = true;
        }
      }
    }
};

/* Set these to your desired credentials. */
const char *ssid = "ELG-Client";
const char *password = "";

ESP8266WebServer server(80);
WiFiWrapper main_wifi;

void setup() {
  // Begin SPIFFS ESP8266 File system
  SPIFFS.begin();
  uint8_t mac[WL_MAC_ADDR_LENGTH];

  // station mode allows both client and AP mode
  WiFi.mode(WIFI_AP_STA);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  WiFi.softAPmacAddress(mac);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: " + myIP);

  // TODO: make a routes page that handles this for us
  // TODO: parse a routes file to handle resources
  // TODO: load preferences from config.json file for NAP, Reverse Geo, and Scan Freq

  // route setup (API Calls)
  server.on("/", handleRoot);
  server.on("/skyhookclient/scan", HTTP_GET, handleScan);
  server.on("/skyhookclient/changeap", HTTP_POST, handleChangeAP);
  server.on("/skyhookclient/getstatus", HTTP_GET, handleGetStatus);
  // server.on("/skyhookclient/getpreferences", HTTP_GET, handlePreferences);
  // server.on("/skyhookclient/getlocation", HTTP_GET, getLocation);
  server.onNotFound(handleNotFound);

  // scripts and css files for the web interface
  server.on("/resources/plugins.min.css", HTTP_GET, handleResources);
  server.on("/resources/picnic.min.css", HTTP_GET, handleResources);
  server.on("/resources/umbrella.min.js", HTTP_GET, handleResources);
  server.on("/resources/animate.min.css", HTTP_GET, handleResources);
  server.on("/resources/skyhook_logo.svg", HTTP_GET, handleResources);

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

// FROM ROUTES: returns ESP connectivity status & info in JSON Format
void handleGetStatus() {
  Serial.println("requesting status");
  DynamicJsonBuffer wifistatus_obj_buf;
  JsonObject& wifistatus_obj = wifistatus_obj_buf.createObject();
  if (WiFi.status() == WL_CONNECTED) {
    wifistatus_obj["connected"] = true;
    wifistatus_obj["ssid"] = WiFi.SSID();
    wifistatus_obj["bssid"] = WiFi.BSSIDstr();
    wifistatus_obj["channel"] = WiFi.channel();
    wifistatus_obj["rssi"] = WiFi.RSSI();
    wifistatus_obj["mac"] = WiFi.macAddress();
    wifistatus_obj["local_ip"] = WiFi.localIP().toString();
  }
  else{
    wifistatus_obj["connected"] = false;
    wifistatus_obj["channel"]=WiFi.channel();
  }
  send_json_response(wifistatus_obj);
}

// Streams the landing page of the web client to the client
void handleRoot() {
  // TODO scan surrounding networks
  // TODO: Server send general HTML with requests for scan list instead of waiting for the scan
  String connection = "";
  if (WiFi.SSID() != NULL && WiFi.status() == WL_CONNECTED) {
    connection = "Connected To: " + WiFi.SSID();
  }
  else {
    connection = "Not connected :(";
  }
  Serial.println("Requesting " + server.uri());

  File f;
  f = SPIFFS.open("/index.html", "r");
  if (!f) {
    Serial.println(server.uri() + " does not exist");
  }
  if (server.streamFile(f, "text/html") != f.size()) {
    Serial.println("Error");
  }
  f.close();
}

// streams the css and scripts of the landing to the user
// TODO: integrate handleRoot into this method
void handleResources() {
  Serial.println("Requesting: " + server.uri());
  // begin file mangament
  String path = server.uri();
  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.htm";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".svg")) dataType = "image/svg+xml";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if(!dataFile){
    Serial.println(path+" not found!");
  }
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
    Serial.println("Error");
  }
  dataFile.close();
}

// Returns a JSON of scanned networks
void handleScan() {
  Serial.println("Scanning Networks");
  int n = WiFi.scanNetworks();
  DynamicJsonBuffer scan_obj_buf;
  JsonObject& scan_obj = scan_obj_buf.createObject();

  for (int i = 0; i < n; i++) {
    DynamicJsonBuffer scan_info_buf;
    JsonObject& scan_info = scan_obj.createNestedObject(WiFi.SSID(i));
    scan_info["bssid"] = WiFi.BSSIDstr(i);
    scan_info["channel"] = WiFi.channel(i);
    scan_info["rssi"] = WiFi.RSSI(i);
    scan_info["encrypt"] = encryptionTypeStr(WiFi.encryptionType(i));
    scan_info["hidden"] = WiFi.isHidden(i);
  }
  send_json_response(scan_obj);
}

// Streams JsonObject to the client with HTTP Status 200
void send_json_response(JsonObject& obj) {
  size_t len = obj.measurePrettyLength();
  char* responseJSON = (char*)malloc((obj.measureLength() + 1) * sizeof(char));
  obj.printTo(responseJSON, obj.measureLength() + 1);
  obj.prettyPrintTo(Serial);
  server.send(200, "application/json", responseJSON);
  free(responseJSON);
}

// TODO: on client side, notify them that changing AP will disconnect them
// Handles POST request, connects to specified AP
// Will disconnect client if AP is on a different channel
void handleChangeAP() {
  Serial.println("User is trying to change AP");
  if (server.hasArg("ssid") && server.hasArg("password")) {
    Serial.println("SSID: " + server.arg("ssid"));
    Serial.println("Password: " + server.arg("password"));
    server.sendHeader("Refresh", "10; url=/");
    // TODO: handle error
    server.send(200, "text/html", "<head></head><h1>Attemping to connect to SSID " + server.arg("ssid") + ". AP will now shut down" + "</h1>");
  }
  // TODO: Tell user that the client will now disconnect and attempt to connect to the AP
  // server send: restarting page
  // OLED: "Attempting to connect to SSID"

  //WIFI.begin() will move the AP channel
  main_wifi.connect_to(server.arg("ssid"), server.arg("pw"));
  Serial.println("Current connection status: " + String(main_wifi.get_init_check_finish()));

  // Checks 
  while (!(main_wifi.get_init_check_finish())) {
    main_wifi.init_check_connection(500);
    delay(1);
    // Serial.println("Checking for interrupts");
    // Run Interrupt Class
  }

  Serial.println("Finished Checking for Wifi Connection");
  if (main_wifi.check_connection()) {
    Serial.println("Connected to WiFi");
    if (save_connected_network(server.arg("password"))) {
      print_saved_networks();
      //server.send(200,"text/html", "<head></head><h1>AP connected and saved</h1>");
    }
    // Send as internval service error if AP can't be saved
    else {
      Serial.println("Couldn't save AP to database");
      //server.send(500,"text/html", "<head></head><h1>Couldn't save AP to database</h1>");
    }
  }
  // Device couldn't connect to AP
  else {
    Serial.println("Failed to Connect");
    //server.send(500, "text/html", "<head></head><h1>Failed to Connect</h1>");
  }
}

void print_saved_networks() {
  char APjson[417];
  if (SPIFFS.exists("/resources/AP.json")) {
    File a = SPIFFS.open("/resources/AP.json", "r");
    a.readBytesUntil(0, APjson, 417);
    a.close();
  }
  DynamicJsonBuffer bssid_obj_buf;
  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);
  bssid_obj.prettyPrintTo(Serial);
}

// Function will save the connected network into JSON formated file
// TODO: Impose number of saved networks (currently magic numbers are
// configured to three bssids
bool save_connected_network(String password) {
  // TODO: make configue file for magic numbers
  // 417 Because of max ssid and password calculation (will document)
  char APjson[417];
  String bssid = WiFi.BSSIDstr();
  Serial.println(bssid);
  // write existing data to a buffer
  if (SPIFFS.exists("/resources/AP.json")) {
    File a = SPIFFS.open("/resources/AP.json", "r");
    a.readBytesUntil(0, APjson, 417);
    a.close();
  }
  // if ssid/pw storage doesn't exist, make an empty json array
  else {
    APjson[0] = '{';
    APjson[1] = '}';
  }

  // dynamic buffers (should only be used for devices with larger RAM)
  DynamicJsonBuffer bssid_obj_buf;
  DynamicJsonBuffer bssid_info_buf;

  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);

  // if the BSSID already exists we will update it by removing it and then
  // readding it (keeping the stack style of BSSID storage)
  if (bssid_obj[bssid] != NULL) {
    bssid_obj.remove(bssid);
  }
  JsonObject& bssid_info = bssid_obj.createNestedObject(bssid);
  bssid_info["ssid"] = WiFi.SSID();
  bssid_info["pw"] = password;

  // remove the tmp file check
  if (!SPIFFS.exists("/resources/APtmp.json")) {
    SPIFFS.remove("/resources/APtmp.json");
  }

  File b = SPIFFS.open("/resources/APtmp.json", "w+");
  // ERROR: file couldn't be open or created
  if (!b) {
    return 0;
  }
  // write to file
  bssid_obj.printTo(b);
  b.close();

  // delete the old AP list and update the new one to have the same name
  SPIFFS.remove("/resources/AP.json");
  SPIFFS.rename("/resources/APtmp.json", "/resources/AP.json");

  // double checks that the JSON exists
  if (SPIFFS.exists("/resources/AP.json")) {
    return 1;
  }
  else {
    return 0;
  }
}

void handleNotFound() {
  server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
}

String encryptionTypeStr(uint8_t authmode) {
  switch (authmode) {
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
