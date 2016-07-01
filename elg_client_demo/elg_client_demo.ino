/************************************************
* Authors: Alexander Lin
* 
* Company: Skyhook Wireless
*
************************************************/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_FeatherOLED.h>
#include <Adafruit_FeatherOLED_WiFi.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "sky_types.h"
#include "sky_protocol_client_1.h"
#include "sky_crypt.h"
#include "config.h"

// for the WiFiWrapper Class for when init_check_connection is called
bool reverse_geo = true;
bool HPE = true;
int scan_frq;

struct aes_key_t key = {USERID, AES_KEY};
struct location_req_t rq;
struct location_resp_t resp;
bool sent;
bool alt;
unsigned long screen_timer = 0;

// TODO: Allow the user to specify to restart in AP mode or Client Mode after AP change
typedef void (*functiontype)();
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

void print_to_oled(String msg1, String msg2);
void print_location_oled();
void change_state();
void update_oled();
void handleRoot();
void handleResources();
void handleScan();
void handleChangeAP();
void handleGetStatus();
void handleGetPreferences();
void handleChangePreferences();
void handleNotFound();

/* Set these to your desired credentials. */
const char *ssid = "ELG-Client";
const char *password = "";

ESP8266WebServer server(80);
WiFiClient client;
Adafruit_FeatherOLED_WiFi oled = Adafruit_FeatherOLED_WiFi();

// Class allows WiFi to connect and check for connection
// status while also handling interrupts
class APWiFiWrapper {
    // denotes if WiFi is currently connected
    unsigned long previousMillis;
    int check_times;
    bool init_check_finish;

  public:
    APWiFiWrapper() {
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

class Button{
  unsigned long previousMillis;
  unsigned long debounce;
  void (*callback)();
  int pin;

  public:
    Button(int pin_number, void (*func)()){
      pin = pin_number;
      pinMode(pin,INPUT_PULLUP);
      previousMillis = 0;
      debounce = 150;
      callback = func;
    }

  bool update(){
    unsigned long now = millis();
    if(now - previousMillis > debounce && digitalRead(pin)==LOW){
      callback(); 
      previousMillis = now;
      screen_timer = 0;
      return true;
    }
    return false;
  }
};
Button state = Button(13, change_state);
class ClientWiFiWrapper{
  bool sent;
  // access point array
  struct ap_t aps[MAX_AP_COUNT];
  uint8_t buff[1024];
  unsigned long txTimer;
  unsigned long rxTimer;
  int check_time;
  
  public:
    ClientWiFiWrapper(){
      sent = false;
      txTimer = 0;
      rxTimer = 0;
      check_time = 0;
    }

  void scan(){
    alt = true;
    int n = WiFi.scanNetworks();
    
    if (n > MAX_AP_COUNT){
      n = MAX_AP_COUNT;
    }
  
    for (int i = 0; i < n; ++i)
    {
        if(state.update()) return;
        aps[i].rssi = (int8_t)WiFi.RSSI(i);
        memcpy(aps[i].MAC, WiFi.BSSID(i), sizeof(aps[i].MAC));
        // delay(10);
        yield();
    }
    // create location request
      rq.key = &key; // assign key
  
      // set mac address
      WiFi.macAddress(rq.MAC);
  
      // set protocol version
      rq.protocol = SKY_PROTOCOL_VERSION;
  
      //rq.payload_type = LOCATION_RQ; // simple location request
      rq.payload_type = LOCATION_RQ_ADDR; // full address lookup
      rq.version = SKY_SOFTWARE_VERSION; // skyhook client library version
      rq.ap_count = n & 0xFF; // set the number of scanned access points
  
      rq.aps = aps; // assign aps
      // in this demo we are not using cell, ble or gps
      // zero counts
      rq.ble_count = 0;
      rq.cell_count = 0;
      rq.gps_count = 0;
  
      int cnt = sky_encode_req_bin_1(buff, sizeof(buff), &rq);
  
      if (cnt == -1)
      {
          Serial.println("failed to encode request");
          return;
      }
  
      /* encrypt buffer, use hardware encryption when available */
      int r = sky_aes_encrypt(buff + REQUEST_HEAD_SIZE_1, cnt - REQUEST_HEAD_SIZE_1, key.aes_key, buff + REQUEST_IV_OFFSET_1);
  
      if (r == -1)
      {
          Serial.println("failed to encrypt");
          return;
      }
  
      // close any connection
      client.stop();
  
      Serial.print("connecting to ");
      Serial.print(SKYHOOK_ELG_SERVER_URL);
      Serial.print(":");
      Serial.println(SKYHOOK_ELG_SERVER_PORT);
  
      if (!client.connect(SKYHOOK_ELG_SERVER_URL, SKYHOOK_ELG_SERVER_PORT))
      {
          Serial.println("connection failed");
          oled.clearDisplay();
          oled.setCursor(0,8);
          oled.println("connection failed....retrying");
          oled.display();
          unsigned long now = millis();
          while(true){
            if(now - millis() > 1000){
              break;
            }
            if(state.update()){
              return;
            }
          }
          return;
      }
  
      size_t wcnt = client.write((const uint8_t *)buff, (size_t)cnt);
  
      Serial.print("sent:");
      Serial.println(wcnt);
      sent = true;
  }
  bool rx(){
      Serial.println("waiting");
  
      int n = client.available();
  
      while(n = client.available())
      {
          Serial.println("data present");
          if(state.update()) return false;
          // trim to buff size
          if (n > sizeof(buff))
          {
              n = sizeof(buff);
          }
  
          n = client.read(buff, n);
          Serial.print("read bytes");
          Serial.println(n);
          memset(&resp.location_ex, 0, sizeof(resp.location_ex)); // clear the values
          resp.key = &key; // assign decryption key
  
          if (sky_aes_decrypt(buff + RESPONSE_HEAD_SIZE_1, n - RESPONSE_HEAD_SIZE_1, key.aes_key, buff + RESPONSE_IV_OFFSET_1) != 0)
          {
              Serial.println("failed to decrypt response");
          }
  
          int res = sky_decode_resp_bin_1(buff, sizeof(buff), n, &resp);
  
          if (res == -1)
          {
              Serial.println("failed to decode response");
          }
  
          print_location_resp(&resp);
  
          Serial.println("Rx done");
          sent = false;
          return true;
      }
    return false;
  }
  void print_location_resp(struct location_resp_t *cr)
  {
    Serial.println();
    Serial.print("timestamp: ");
//    print_u64(cr->timestamp);
/*
    char str[100];
    sprintf(str, "%" PRIu64, cr->timestamp);
    Serial.println(str);
*/
    Serial.print("protocol: "); Serial.println(cr->protocol);
    Serial.print("server version: "); Serial.println(cr->version);
    Serial.print("payload type no: "); Serial.println(cr->payload_type);
    
    // http codes
    if (cr->payload_type < HTTP_UNKNOWN && cr->payload_type >= HTTP_200)
    {
        int err;
        if (cr->payload_type > HTTP_505) err = HTTP_UNKNOWN;
        else if (cr->payload_type >= HTTP_500) err = cr->payload_type - HTTP_500 + 500;
        else if (cr->payload_type > HTTP_417) err = HTTP_UNKNOWN;
        else if (cr->payload_type >= HTTP_400) err = cr->payload_type - HTTP_400 + 400;
        else if (cr->payload_type > HTTP_307) err = HTTP_UNKNOWN;
        else if (cr->payload_type >= HTTP_300) err = cr->payload_type - HTTP_300 + 300;
        else if (cr->payload_type > HTTP_206) err = HTTP_UNKNOWN;
        else if (cr->payload_type >= HTTP_200) err = cr->payload_type - HTTP_200 + 200;
        else err = HTTP_UNKNOWN;

        Serial.print("HTTP "); Serial.println(err);
    }
    else
    {
        switch (cr->payload_type)
        {
            case PAYLOAD_ERROR: Serial.println("PAYLOAD_ERROR"); break;
            case PAYLOAD_API_ERROR: Serial.println("PAYLOAD_API_ERROR"); break;
            case SERVER_ERROR: Serial.println("SERVER_ERROR"); break;
            case LOCATION_RQ_ERROR: Serial.println("LOCATION_RQ_ERROR"); break;
            case PAYLOAD_NONE: Serial.println("PAYLOAD_NONE"); break;
            case PROBE_REQUEST: Serial.println("PROBE_REQUEST"); break;
            case DECODE_BIN_FAILED: Serial.println("DECODE_BIN_FAILED"); break;
            case ENCODE_BIN_FAILED: Serial.println("ENCODE_BIN_FAILED"); break;
            case DECRYPT_BIN_FAILED: Serial.println("DECRYPT_BIN_FAILED"); break;
            case ENCRYPT_BIN_FAILED: Serial.println("ENCRYPT_BIN_FAILED"); break;
            case ENCODE_XML_FAILED: Serial.println("ENCODE_XML_FAILED"); break;
            case DECODE_XML_FAILED: Serial.println("DECODE_XML_FAILED"); break;
            case SOCKET_FAILED: Serial.println("SOCKET_FAILED "); break;
            case SOCKET_WRITE_FAILED: Serial.println("SOCKET_WRITE_FAILED"); break;
            case SOCKET_READ_FAILED: Serial.println("SOCKET_READ_FAILED"); break;
            case SOCKET_TIMEOUT_FAILED: Serial.println("SOCKET_TIMEOUT_FAILED"); break;
            case CREATE_META_FAILED: Serial.println("CREATE_META_FAILED"); break;
            case HTTP_UNKNOWN: Serial.println("HTTP_UNKNOWN"); break;
        }
    }

    if (cr->payload_type != LOCATION_RQ &&
        cr->payload_type != LOCATION_RQ_ADDR) return;

    Serial.println("LOCATION_RQ");
    Serial.print("latitude: "); Serial.println(cr->location.lat, 6);
    Serial.print("longitude: "); Serial.println(cr->location.lon, 6);
    Serial.print("hpe: "); Serial.println(cr->location.hpe);
    
    if (cr->payload_type == LOCATION_RQ_ADDR)
    {
        Serial.println("LOCATION_RQ_ADDR");
        Serial.print("distance_to_point: "); Serial.println(cr->location_ex.distance_to_point);
        Serial.print("street num: "); print_s(cr->location_ex.street_num, cr->location_ex.street_num_len);
        Serial.print("address: "); print_s(cr->location_ex.address, cr->location_ex.address_len);
        Serial.print("city: "); print_s(cr->location_ex.city, cr->location_ex.city_len);
        Serial.print("state: "); print_s(cr->location_ex.state, cr->location_ex.state_len);
        Serial.print("state code: "); print_s(cr->location_ex.state_code, cr->location_ex.state_code_len);
        Serial.print("postal code: "); print_s(cr->location_ex.postal_code, cr->location_ex.postal_code_len);
        Serial.print("county: "); print_s(cr->location_ex.county, cr->location_ex.county_len);
        Serial.print("country: "); print_s(cr->location_ex.country, cr->location_ex.country_len);
        Serial.print("country code: "); print_s(cr->location_ex.country_code, cr->location_ex.country_code_len);
        Serial.print("metro1: "); print_s(cr->location_ex.metro1, cr->location_ex.metro1_len);
        Serial.print("metro2: "); print_s(cr->location_ex.metro2, cr->location_ex.metro2_len);
        Serial.print("ip: "); print_ip(cr->location_ex.ipaddr, cr->location_ex.ip_type);
    }
  }
  void print_s(char *buff, int len)
  {
      int i;
      for (i = 0; i < len; i++)
      {
          Serial.print(buff[i]);
      }
  
      Serial.println();
  }
  void print_ip(unsigned char *ip, unsigned char ip_type)
  {
      if (ip == NULL) return;
  
      int i;
  
      if (ip_type == DATA_TYPE_IPV6)
      {
          char z = 0;
  
          for (i = 0; i < 8; i++)
          {
              if (ip[i] == 0 && ip[i+1] == 0)
              {
                  z = 1;
                  continue;
              }
  
              if (z) Serial.print(":");
              Serial.print(ip[i], HEX);
              Serial.print(ip[i+1, HEX]);
              Serial.print(":");
              z = 0;
          }
      }
      else
      {
          for (i = 0; i < 4; i++)
          {
              Serial.print(ip[i]);
              if (i < 3) Serial.print(".");
          }
      }
      Serial.println();
  }
  void handle(){
    unsigned long now = millis();
    if(WiFi.status() == WL_CONNECTED){
      if(!sent){
        // 10000
        if(now-txTimer > scan_frq){
          scan();
          txTimer = now;
          rxTimer = now;
        }
      }
      else{//2500
        if(now - rxTimer > WIFI_RX_WAIT_TIME && check_time < 150){
          Serial.println("waijti");
          if(rx()){
            rxTimer = now;
            print_location_oled();
            check_time = 0;
          }
          else{
            Serial.println("No Repsonse, retyring");
            check_time++;
          }
          if(check_time >= 150){
            oled.clearDisplay();
            oled.setCursor(0,8);
            oled.println("No response, dumping request");
            oled.display();
            check_time = 0;
            sent = false;
          }
        }
      }
    }
    else{
      oled.clearMsgArea();
      update_oled();
      oled.refreshIcons();
      print_to_oled("Wifi Disconnected","");
      if(state.update()){
        sent = false; 
        check_time = 0;
        return;
      }
      yield();
    }
    yield();
  }

  void location_json(){
    while(true){
      unsigned long now = millis();
      if(WiFi.status() == WL_CONNECTED){
        if(!sent){
          // 10000
          if(now-txTimer > scan_frq){
            scan();
            txTimer = now;
            rxTimer = now;
          }
        }
        else{//2500
          if(now - rxTimer > WIFI_RX_WAIT_TIME && check_time < 150){
            Serial.println("waijti");
            if(rx()){
              rxTimer = now;
              check_time = 0;
              char buf[10];
              String address = "\"";
              snprintf(buf, (10 > resp.location_ex.street_num_len ? resp.location_ex.street_num_len + 1 : 10), "%s", resp.location_ex.street_num);
              address += String(buf) + " ";
              snprintf(buf, (10 > resp.location_ex.address_len ? resp.location_ex.address_len + 1 : 10), "%s", resp.location_ex.address);
              address += String(buf) + " ";
              snprintf(buf, (10 > resp.location_ex.metro1_len ? resp.location_ex.metro1_len + 1 : 10), "%s", resp.location_ex.metro1);
              address += String(buf) + " ";
              snprintf(buf, (10 > resp.location_ex.state_code_len ? resp.location_ex.state_code_len + 1 : 10), "%s", resp.location_ex.state_code);
              address += String(buf) + " ";
              snprintf(buf, (10 > resp.location_ex.postal_code_len ? resp.location_ex.postal_code_len + 1 : 10), "%s", resp.location_ex.postal_code);
              address += String(buf)+"\"";
              server.send(200,"application/json","{\"LAT\": "+String(resp.location.lat,5)+", \"LON\":"+String(resp.location.lon,5)+", \"reverse_geo\":"+address+"}");
              return;
            }
            else{
              Serial.println("No Repsonse, retyring");
              check_time++;
            }
            if(check_time >= 150){
              check_time = 0;
              sent = false;
              server.send(500,"application/json","{\"error\":\"No Response From ELG Server\"}");
              return;
            }
          }
        }
      }
      else{
        server.send(500,"application/json","{\"error\":\"WiFi Disconnected\"}");
      }
      yield();
    }
  }
};

APWiFiWrapper main_wifi;
ClientWiFiWrapper client_req;
int esp_state = 1;

void setup() {
/* Uncomment the next line to make the RST pin/button a soft on/off button*/
//  determine_on_state();
  Serial.begin(115200);

  oled.init();
  oled.clearDisplay();

  // Begin SPIFFS ESP8266 File system
  SPIFFS.begin();
  scan_frq = SCAN_DEFAULT_FRQ;
  Serial.println("LOADING CONFIG");
  load_config();
  Serial.println("Currently On");

  uint8_t mac[WL_MAC_ADDR_LENGTH];

  // station mode allows both client and AP mode
  WiFi.mode(WIFI_AP_STA);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  WiFi.softAPmacAddress(mac);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP IP address: " + myIP);

  // TODO: make a routes page that handles this for us
  // TODO: parse a routes file to handle resources
  // TODO: load preferences from preferences.json file for NAP, Reverse Geo, and Scan Freq

  // route setup (API Calls)
  server.on("/", handleRoot);
  server.on("/skyhookclient/scan", HTTP_GET, handleScan);
  server.on("/skyhookclient/changeap", HTTP_POST, handleChangeAP);
  server.on("/skyhookclient/getstatus", HTTP_GET, handleGetStatus);
  server.on("/skyhookclient/getpreferences", HTTP_GET, handleGetPreferences);
  server.on("/skyhookclient/changepreferences", HTTP_POST, handleChangePreferences);
  server.on("/skyhookclient/getlocation", HTTP_GET, handleLocation);
  server.onNotFound(handleNotFound);

  // scripts and css files for the web interface
  server.on("/resources/plugins.min.css", HTTP_GET, handleResources);
  server.on("/resources/picnic.min.css", HTTP_GET, handleResources);
  server.on("/resources/umbrella.min.js", HTTP_GET, handleResources);
  server.on("/resources/animate.min.css", HTTP_GET, handleResources);
  server.on("/resources/skyhook_logo.svg", HTTP_GET, handleResources);

  server.begin();
  Serial.println("HTTP server started");
  print_to_oled("Client","");
  update_oled();
  oled.refreshIcons();
}

void handleLocation(){
  client_req.location_json();
}

void loop() {
  // we will have a state here that will keep track of AP-Mode vs Client-Mode
  if(esp_state == AP){
    server.handleClient();
    update_oled();
    oled.refreshIcons();
  }
  else{
    client_req.handle();
  }
  // Serial.println(esp_state);
  state.update();
  yield();
}

void load_config(){
  String config_json;
  if (SPIFFS.exists("/resources/preferences.json")) {
    File a = SPIFFS.open("/resources/preferences.json", "r");
    Serial.println("Reading file........");
    while(a.available()){
      config_json += (char)a.read();
    }
    Serial.println("printing cconfig");
    Serial.println(config_json);
    a.close();
  }
  else{
    Serial.println("Config not found!");
  }
  DynamicJsonBuffer config_obj_buf;
  JsonObject& config_obj = config_obj_buf.parseObject(config_json);
  scan_frq = config_obj["scan_freq"];
  HPE = config_obj["HPE"];
  reverse_geo = config_obj["reverse_geo"];

  Serial.println("config json");
  config_obj.printTo(Serial);
}

void handleGetPreferences(){
  String config_json;
  if (SPIFFS.exists("/resources/preferences.json")) {
    File a = SPIFFS.open("/resources/preferences.json", "r");
    if (server.streamFile(a, "application/json") != a.size()) {
      Serial.println("Error");
    }
  }
}
  
void change_state(){
  esp_state = !esp_state;
  if(esp_state == AP){
    print_to_oled("AP", "");
  }
  else{
    print_to_oled("Client", "");
  }
}

void handleChangePreferences(){
  Serial.println("User is trying to change Preferences");
  String preferences;
  if (server.hasArg("HPE") && server.hasArg("reverse_geo") && server.hasArg("scan_freq")) {
    String HPE_user = server.arg("HPE");

    if (SPIFFS.exists("/resources/preferences.json")) {
      File a = SPIFFS.open("/resources/preferences.json", "r");
      while(a.available()){
        preferences += (char)a.read();
      }
      a.close();
      Serial.println("before");
      Serial.println(preferences);
      //a.seek(0,SeekSet);
      
      DynamicJsonBuffer pref_obj_buf;
      JsonObject& pref_obj = pref_obj_buf.parseObject(preferences);
      pref_obj["HPE"] = string_to_bool(server.arg("HPE"));
      pref_obj["reverse_geo"] = string_to_bool(server.arg("reverse_geo"));
      int scan_freq_input = server.arg("scan_freq").toInt();
      if(scan_freq_input < 200){
        scan_freq_input = SCAN_DEFAULT_FRQ;
      }
      pref_obj["scan_freq"] = scan_freq_input;

      if (!SPIFFS.exists("/resources/preferencesTmp.json")) {
        SPIFFS.remove("/resources/preferencesTmp.json");
      }
    
      File b = SPIFFS.open("/resources/preferencesTmp.json", "w");
      // ERROR: file couldn't be open or created
      if (!b) {
        server.send(500);
        return;
      }
      // write to file
      pref_obj.printTo(b);
      b.close();

      Serial.println("after");
      pref_obj.printTo(Serial);
      
      // delete the old AP list and update the new one to have the same name
      SPIFFS.remove("/resources/preferences.json");
      SPIFFS.rename("/resources/preferencesTmp.json", "/resources/preferences.json");
    
      // double checks that the JSON exists
      if (SPIFFS.exists("/resources/preferences.json")) {
        server.send(200, "application/json", "{\"error\":\"none\"}");
      }
      else {
        server.send(500);
      }
    }
    else{
      Serial.println("uhh no config file");
      server.send(500, "application/json", "{\"error\":\"config file not found\"}");
    }
  }
  else{
    Serial.println("incomplete request");
  }
}

bool string_to_bool(String input){
  input.toLowerCase();
  if(input == "true"){
    return true;
  }
  else{
    return false;
  }
}

void update_oled(){
  update_voltage();
  uint32_t ip = (uint32_t)WiFi.localIP();
  oled.setRSSI(WiFi.RSSI());
  oled.setIPAddress(ip);
  oled.setConnected(main_wifi.check_connection());
}

//void determine_on_state(){
//  EEPROM.begin(1);
//  byte value = EEPROM.read(0);
//  EEPROM.write(0, !value);
//  EEPROM.commit();
//  EEPROM.end();
//  if(!(bool)value){
//    ESP.deepSleep(0);
//  }
//}

void update_voltage(){
  float vBat = (analogRead(A0) * 5.0) / 1024.0;
  oled.setBattery(vBat);
}

void print_to_oled(String msg1, String msg2){
  oled.clearMsgArea();
  oled.println(msg1);
  if(msg2 != ""){
    oled.println(msg2);
  }
  oled.display();
  oled.refreshIcons();
}

void print_location_oled(){
  unsigned long start_time = millis();
  unsigned long page1_display_timer = (unsigned long)scan_frq/2;
  bool page1_done = false;
  bool page2_done = false;
  if(!reverse_geo){
    page1_display_timer = scan_frq;
    page2_done = true;
  }
  //Serial.println(page1_display_timer);
  while(true){
    unsigned long now = millis();
    if(!page1_done){
      oled.clearDisplay();
      oled.setCursor(0,0);
      oled.println("INFO:");
      oled.println("LAT: " + String(resp.location.lat, 5));
      oled.println("LON: " + String(resp.location.lon, 5));
      if(HPE){
        oled.println("HPE: " + String(resp.location.hpe, 5));
      }
      oled.display();
      page1_done = true;
    }
    if(now - start_time > page1_display_timer && !page2_done){
      oled.clearDisplay();
      oled.setCursor(0,0);
      oled.println("ADDRESS:");
      char buff[10];
      snprintf(buff, (10 > resp.location_ex.street_num_len ? resp.location_ex.street_num_len + 1 : 10), "%s", resp.location_ex.street_num);
      oled.print(buff);
      oled.write(' ');
      snprintf(buff, (10 > resp.location_ex.address_len ? resp.location_ex.address_len + 1 : 10), "%s", resp.location_ex.address);
      oled.print(buff);
      oled.write(' ');
      snprintf(buff, (10 > resp.location_ex.metro1_len ? resp.location_ex.metro1_len + 1 : 10), "%s", resp.location_ex.metro1);
      oled.print(buff);
      oled.write(' ');
      snprintf(buff, (10 > resp.location_ex.state_code_len ? resp.location_ex.state_code_len + 1 : 10), "%s", resp.location_ex.state_code);
      oled.print(buff);
      oled.write(' ');
      snprintf(buff, (10 > resp.location_ex.postal_code_len ? resp.location_ex.postal_code_len + 1 : 10), "%s", resp.location_ex.postal_code);
      oled.println(buff);
      oled.display();
      page2_done = true;
    }
    if(now - start_time > (unsigned long)scan_frq){
      Serial.println("Display done");
      break;
    }
    if(state.update()) return;
    yield();
  }
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
  if (WiFi.SSID() != "" && WiFi.status() == WL_CONNECTED) {
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
  print_to_oled("Scanning Networks", "");
  int n = WiFi.scanNetworks();
  DynamicJsonBuffer scan_obj_buf;
  JsonObject& scan_obj = scan_obj_buf.createObject();

  for (int i = 0; i < n; i++) {
    if(state.update()) return;
    
    DynamicJsonBuffer scan_info_buf;
    JsonObject& scan_info = scan_obj.createNestedObject(WiFi.SSID(i));
    scan_info["bssid"] = WiFi.BSSIDstr(i);
    scan_info["channel"] = WiFi.channel(i);
    scan_info["rssi"] = WiFi.RSSI(i);
    scan_info["encrypt"] = encryptionTypeStr(WiFi.encryptionType(i));
    scan_info["hidden"] = WiFi.isHidden(i);
  }
  send_json_response(scan_obj);
  oled.clearMsgArea();
}


// Streams JsonObject to the client with HTTP Status 200
void send_json_response(JsonObject& obj) {
  size_t len = obj.measurePrettyLength();
  char* responseJSON = (char*)malloc((obj.measureLength() + 1) * sizeof(char));
  obj.printTo(responseJSON, obj.measureLength() + 1);
  // obj.prettyPrintTo(Serial);
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

  print_to_oled("Connecting to: " + server.arg("ssid"), "");

  // TODO: Tell user that the client will now disconnect and attempt to connect to the AP
  // server send: restarting page
  // OLED: "Attempting to connect to SSID"

  //WIFI.begin() will move the AP channel
  main_wifi.connect_to(server.arg("ssid"), server.arg("password"));
  Serial.println("Current connection status: " + String(main_wifi.get_init_check_finish()));

  // Checks 
  while (!(main_wifi.get_init_check_finish())) {
    main_wifi.init_check_connection(500);
    if(state.update()) return;
    yield();
    // Serial.println("Checking for interrupts");
    // Run Interrupt Class
  }

  Serial.println("Finished Checking for Wifi Connection");
  if (main_wifi.check_connection()) {
    Serial.println("Connected to WiFi");
    print_to_oled("Connected To: "+  WiFi.SSID(), "");

    if (save_connected_network(server.arg("password"))) {
      // print_saved_networks();
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
    print_to_oled("Failed to Connect", "");
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
void print_saved_preferences(){
  String pref;
  if (SPIFFS.exists("/resources/preferences.json")) {
    File a = SPIFFS.open("/resources/preferences.json", "r");
    while(a.available()){
      pref += (char)a.read();
    }
  }
  DynamicJsonBuffer bssid_obj_buf;
  JsonObject& bssid_obj = bssid_obj_buf.parseObject(pref);
  bssid_obj.prettyPrintTo(Serial);
}
// Function will save the connected network into JSON formated file
// TODO: Impose number of saved networks (currently magic numbers are
// configured to three bssids
bool save_connected_network(String password) {
  // TODO: make configue file for magic numbers
  // 417 Because of max ssid and password calculation (will document)
  String APjson;
  String bssid = WiFi.BSSIDstr();
  Serial.println(bssid);
  // write existing data to a buffer
  if (SPIFFS.exists("/resources/AP.json")) {
    File a = SPIFFS.open("/resources/AP.json", "r");
    while(a.available()){
      APjson += (char)a.read();
    }
    a.close();
  }
  // if ssid/pw storage doesn't exist, make an empty json array
  else {
    APjson="{}";
  }

  // dynamic buffers (should only be used for devices with larger RAM)
  DynamicJsonBuffer bssid_obj_buf;
  DynamicJsonBuffer bssid_info_buf;

  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);

  // if the BSSID already exists we will update it by removing it and then
  // readding it (keeping the stack style of BSSID storage)
  if (bssid_obj[bssid] != "") {
    bssid_obj.remove(bssid);
  }
  JsonObject& bssid_info = bssid_obj.createNestedObject(bssid);
  bssid_info["ssid"] = WiFi.SSID();
  bssid_info["pw"] = password;

  bssid_obj.prettyPrintTo(Serial);

  // remove the tmp file check
  if (!SPIFFS.exists("/resources/APtmp.json")) {
    SPIFFS.remove("/resources/APtmp.json");
  }

  File b = SPIFFS.open("/resources/APtmp.json", "w");
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



