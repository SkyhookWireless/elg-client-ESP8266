/************************************************
* Authors: Alexander Lin, Istvan Sleder, and Marwan Kallal
* 
* Company: Skyhook Wireless
*
************************************************/
#include <Adafruit_FeatherOLED_WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <time.h>
#include "FS.h"
#include <ArduinoJson.h>
#include <EEPROM.h>
#include "sky_crypt.h"
#include "sky_protocol.h"
#include "config.h"
#include <math.h>
#include <Wire.h>
#include <LiFuelGauge.h>

/* returns number of result bytes that were successfully parsed */
uint32_t hex2bin(const char *hexstr, uint32_t hexlen, uint8_t *result, uint32_t reslen) {
    uint32_t i, j = 0, k = 0;

    for (i = 0; i < hexlen; i++) {
        uint8_t c = (uint8_t) hexstr[i];

        if (c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'a' && c <= 'f')
            c = (uint8_t) ((c - 'a') + 10);
        else if (c >= 'A' && c <= 'F')
            c = (uint8_t) ((c - 'A') + 10);
        else
            continue;

        // assign every other hex byte to lower or upper 4 bit
        if (k++ & 0x01)
            result[j++] |= c;
        else
            result[j] = c << 4;

        if (j >= reslen)
            break;
    }

    return j;
}

//startup logo
static const unsigned char PROGMEM skyhook_logo [] = {
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0x3F,
0xFC, 0x01, 0xF0, 0xF3, 0xC1, 0xF0, 0xF0, 0xF0, 0xFC, 0x01, 0xFF, 0x00, 0x7E, 0x1E, 0x0C, 0x1F,
0xFC, 0x00, 0xF0, 0xE1, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0x00, 0xFE, 0x00, 0x3E, 0x1C, 0x1C, 0x0F,
0xF8, 0x01, 0xF0, 0xC1, 0xE0, 0xC1, 0xF0, 0xF0, 0xF0, 0x00, 0x7C, 0x00, 0x1E, 0x18, 0x3C, 0x8F,
0xF8, 0x61, 0xF0, 0x81, 0xF0, 0x41, 0xF0, 0xF0, 0xF0, 0x70, 0x38, 0x1C, 0x1E, 0x10, 0x7C, 0x1F,
0xF8, 0x3F, 0xF0, 0x03, 0xF8, 0x03, 0xF0, 0xF0, 0xE0, 0xF8, 0x38, 0x3E, 0x0E, 0x00, 0xFC, 0x1F,
0xF8, 0x07, 0xF0, 0x07, 0xF8, 0x07, 0xF0, 0x00, 0xE1, 0xFC, 0x38, 0x7F, 0x0E, 0x01, 0xFF, 0xFF,
0xF8, 0x01, 0xF0, 0x07, 0xFC, 0x07, 0xF0, 0x00, 0xE1, 0xFC, 0x38, 0x7F, 0x0E, 0x01, 0xFF, 0xFF,
0xFC, 0x00, 0xF0, 0x07, 0xFC, 0x0F, 0xF0, 0x00, 0xE1, 0xFC, 0x38, 0x7F, 0x0E, 0x00, 0xFF, 0xFF,
0xFF, 0x80, 0xF0, 0x03, 0xFE, 0x0F, 0xF0, 0x00, 0xE0, 0xFC, 0x38, 0x7F, 0x0E, 0x00, 0x7F, 0xFF,
0xFC, 0xF0, 0xF0, 0x41, 0xFE, 0x1F, 0xF0, 0xF0, 0xE0, 0xF8, 0x38, 0x3E, 0x0E, 0x00, 0x7F, 0xFF,
0xF8, 0x20, 0xF0, 0xC1, 0xFE, 0x1F, 0xF0, 0xF0, 0xF0, 0x30, 0x38, 0x08, 0x1E, 0x18, 0x3F, 0xFF,
0xF0, 0x00, 0xF0, 0xE0, 0xFE, 0x1F, 0xF0, 0xF0, 0xF0, 0x00, 0x7C, 0x00, 0x1E, 0x1C, 0x1F, 0xFF,
0xF8, 0x01, 0xF0, 0xF0, 0x7E, 0x1F, 0xF0, 0xF0, 0xF8, 0x00, 0xFE, 0x00, 0x3E, 0x1C, 0x0F, 0xFF,
0xFC, 0x01, 0xF0, 0xF0, 0x3E, 0x1F, 0xF0, 0xF0, 0xFC, 0x01, 0xFF, 0x00, 0x7E, 0x1E, 0x0F, 0xFF,
0xFF, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8F, 0xFF, 0xE3, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

void print_buff(uint8_t *buff, int32_t len) {
    int32_t i;
    int32_t j = 0;

    char tmp[16];
     for (int i=0; i<len; i++) { 
       sprintf(tmp, "%02X",buff[i]); 
       Serial.print(tmp); Serial.print(" ");
       if (++j > 15) {
            j = 0;
            Serial.print("\n");
        }
     }
     Serial.print("\n");
}

// globals for preferences
bool reverse_geo = true;
bool HPE = true;
int scan_frq;

// gloabls required for location request and response
struct sky_key_t key = {USERID, AES_KEY};
struct location_rq_t rq;
struct location_rsp_t resp;
bool sent;

// function type
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

// class declarations
class Button;
class APWiFiWrapper;
class deviceInfo;
class ClientWiFiWrapper;

// reads preferences settings (preferences.json) and loads their values
void load_config();

// changes DeviceInfo device state
void change_device_state();

// streams json object to client
void send_json_response(JsonObject& obj);

// returns encryption type in a more readable format
String encryptionTypeStr(uint8_t authmode);

// converts "true"/"false" to their boolean values
bool string_to_bool(String a);

// stores the file contents into a String
bool file_to_string(String path, const char* type, String& ret_buf);

// prints a and message b on msgArea specified by oled feather library in seperate lines
void print_to_oled(String a, String b);

// prints the currently location in location_rsp_t struct to oled
void print_location_oled();

// sends the index.htm page to the client
void handleRoot();

// sends the requested file (if exists) to the client
void handleResources();

// scans surrounding APs and sends AP info via json to client
void handleScan();

// will attempt to connect to client specified AP
void handleChangeAP();

// gets basic connection info from device
void handleGetStatus();

// gets HPE, reverse_geo, and scan_req values and sends them in json format
void handleGetPreferences();

// handles client specified modification to HPE, reverse_geo, and scan_req values
void handleChangePreferences();

// if file not found send 404
void handleNotFound();

// handles a single location request in AP mode, returns info via json
void handleLocation();

void insert_bssid_info(JsonObject& info, int index);

bool get_error(String& error);
int get_max(int buf[], int len);
void print64(uint64_t value);

void print_saved_networks();
void print_saved_preferences();


/* Set these to your desired credentials. */
const char *ssid = "ELG-Client";
const char *password = "";

ESP8266WebServer server(80);
WiFiClient client;
Adafruit_FeatherOLED_WiFi oled = Adafruit_FeatherOLED_WiFi();
LiFuelGauge gauge(MAX17043);

class Button{
  unsigned long previousMillis;
  void (*callback)();
  int pin;
  int reading;

  // initalizes given the pin on the featherboard that the button is attached to
  public:
    Button(int pin_number, void (*func)(), uint8_t type){
      pin = pin_number;
      if(type == INPUT_PULLUP){
        reading = LOW;
      }
      else{
        reading = HIGH;
      }
      pinMode(pin, type);
      previousMillis = 0;
      callback = func;
    }

  // detects button presses
  bool update(){
    unsigned long now = millis();
    if(now - previousMillis > BUTTON_DEBOUNCE && digitalRead(pin)==reading){
      callback(); 
      previousMillis = now;
      return true;
    }
    return false;
  }
};

Button state = Button(0, change_device_state, INPUT_PULLUP);

// class for AP mode
class APWiFiWrapper {
    unsigned long previousMillis;
    int check_times;
    bool init_check_finish;

  public:
    APWiFiWrapper() {
      check_times = 0;
      init_check_finish = false;
    }

    // will be set to true when init_check_connect sets the value
    bool get_init_check_finish() {
      return init_check_finish;
    }

    // attempts to connect to specified AP, run init_check_connection after
    bool connect_to(String ssid, String password) {
      if(WiFi.status() == WL_CONNECTED){
        WiFi.disconnect();
      }
      WiFi.begin(ssid.c_str(), password.c_str());
      // resets the check flag
      init_check_finish = false;
      previousMillis = 0;
      check_times = 0;

      int status = WiFi.status();
      while(status != WL_CONNECTED && status != WL_NO_SSID_AVAIL && status != WL_CONNECT_FAILED) {
          if(state.update()){return false;}
          yield();
          delay(10);
          status = WiFi.status();
      }
      if(status == WL_CONNECTED){
        return true;
      }
      else{
        return false;
      }
    }

    // resets AP class and WiFi connection
    void connection_reset() {
      if(WiFi.status() == WL_CONNECTED){
        WiFi.disconnect();
      }
      check_times = 0;
      init_check_finish = false;
    }

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

    bool save_connected_network(String password) {
      String APjson;
      String bssid = WiFi.BSSIDstr();
      String ssid = WiFi.SSID();
      Serial.println(ssid);
      if (!file_to_string("/resources/AP.json", "r",APjson)) {
        APjson="{}";
      }

      // initialize JSON object
      DynamicJsonBuffer ssid_obj_buf;
      JsonObject& ssid_obj = ssid_obj_buf.parseObject(APjson);
    
      // if the BSSID already exists remove and readd (keep the stack style of BSSID storage)
      if (ssid_obj[ssid] != "") {
        ssid_obj.remove(ssid);
      }
      
      JsonObject& ssid_info = ssid_obj.createNestedObject(ssid);
      ssid_info["bssid"] = bssid;
      ssid_info["pw"] = password;
    
      // DEBUGGING
      ssid_obj.prettyPrintTo(Serial);
    
      //if # of bssids > MAX_AUTOJOIN_APS then remove the oldest (top of the stack)
      while(ssid_obj.size() > MAX_AUTOJOIN_APS){
        JsonObject::iterator it=ssid_obj.begin();
        ssid_obj.remove(it->key);
      }
    
      // remove the tmp file check
      if (!SPIFFS.exists("/resources/APtmp.json")) {
        SPIFFS.remove("/resources/APtmp.json");
      }
    
      File b = SPIFFS.open("/resources/APtmp.json", "w");
      // ERROR: file couldn't be open or created
      if (!b) {
        return false;
      }
      // write to file
      ssid_obj.printTo(b);
      b.close();
    
      // delete the old AP list and update the new one to have the same name
      SPIFFS.remove("/resources/AP.json");
      SPIFFS.rename("/resources/APtmp.json", "/resources/AP.json");
    
      // double checks that the JSON exists
      if (SPIFFS.exists("/resources/AP.json")) {
        return true;
      }
      else {
        return false;
      }
    }

    // streams json object to client
    void send_json_response(JsonObject& obj) {
      size_t len = obj.measurePrettyLength();
      char* responseJSON = (char*)malloc((obj.measureLength() + 1) * sizeof(char));
      obj.printTo(responseJSON, obj.measureLength() + 1);
      // obj.prettyPrintTo(Serial);
      server.send(200, "application/json", responseJSON);
      optimistic_yield(200);
      free(responseJSON);
    }
};

APWiFiWrapper main_wifi;

class deviceInfo{
  unsigned long now;
  unsigned long last_update;
  int esp_state;
  
  public:
    deviceInfo(){
      now = millis();
      last_update = 0;
      esp_state = INITIAL_STARTUP_STATE;
    }

  // updates OLED and device info every 
  void handle(){
    if(state.update()){
      return;
    }
    now = millis();
    if(now - last_update > DEVICE_UPDATE_RATE){
      update_oled(); 
      last_update = now;
    }
  }

  // updates displayed network info
  void update_oled(){
    update_voltage();
    if(WiFi.status() == WL_CONNECTED){
        oled.setRSSI(WiFi.RSSI());
    }
    else{
      oled.setRSSI(0);
    }
    oled.setIPAddress((uint32_t)WiFi.localIP());
    oled.refreshIcons();
  }

  // reads voltage from battery
  void update_voltage(){
    oled.setBattery(gauge.getVoltage(), gauge.getSOC());
    if(gauge.getSOC() <= ALERT_THRESHOLD){
      oled.setBatteryLow(true);
    }
    else{
      oled.setBatteryLow(false);
    }
  }

  void set_state_settings(){
    if(esp_state == AP){
      oled.setConnected(AP);
      oled.setConnectedVisible(true);
      oled.setRSSIVisible(true);
      oled.setIPAddressVisible(true);
      oled.setVoltageVisible(true);
      //print_to_oled("AP", "");
      print_to_oled("Open in browswer:", WiFi.softAPIP().toString());
      update_oled();
    }
    else{
      //print_to_oled("Client", "");
      oled.setConnected(CLIENT);
      oled.setConnectedVisible(false);
      oled.setRSSIVisible(false);
      oled.setIPAddressVisible(false);
      oled.setVoltageVisible(false);
      oled.refreshIcons();
      
      update_oled();
      //device.update_oled();
    }
  }

  void change_state(){
    oled.clearDisplay();
    esp_state = !esp_state;
    set_state_settings();
    Serial.println("---------- Device State Changed ----------");
  }

  int getDeviceState(){
    return esp_state;
  }
};

deviceInfo device;

// used during setup when connecting to multiple saved networks from AP.json
ESP8266WiFiMulti WiFiMulti;

// class used when on Client mode
class ClientWiFiWrapper{
  bool sent;
  // access point array
  struct ap_t aps[MAX_AP_COUNT];
  // stores response
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

  // loads AP's from AP.json and attempts to connect to one of them
  void conn_known_ap(){
    unsigned long now = millis();
    int check_times = 0;
    bool init_check_finish = false;

    String APjson;
    // write existing data to a buffer
    if (!file_to_string("/resources/AP.json","r",APjson)) {
      // if there is no AP.json file then no AP's to load
      return;
    }

    DynamicJsonBuffer bssid_obj_buf;
    JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);

    for (JsonObject::iterator it=bssid_obj.begin(); it!=bssid_obj.end(); ++it)
    {
      String ssid = it->key;
      String pw = bssid_obj[it->key]["pw"];
      Serial.println(ssid);
      Serial.println(pw);
      WiFiMulti.addAP(ssid.c_str(), pw.c_str());
    }
    WiFi.scanNetworks(false,true);
    Serial.println(str_status[WiFiMulti.run()]);
    WiFi.scanDelete();
  }

  // scans surrounding AP's and sends info to elg server
  void scan(){
    uint8_t * buff = NULL;
    SKY_LOCAL_BYTE_BUFF_32(buff,SKY_PROT_BUFF_LEN);

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
      rq.key = key; // assign key
  
      // set mac address
      uint8_t mac[WL_MAC_ADDR_LENGTH];
      rq.mac = mac;
      WiFi.macAddress(rq.mac);
  
      // set protocol version
      rq.header.version = SKY_PROTOCOL_VERSION;

      rq.payload_ext.payload.sw_version = 1;
  
      //rq.payload_ext.payload.type = LOCATION_RQ; // simple location request
      rq.payload_ext.payload.type = LOCATION_RQ_ADDR; // full address lookup
      //rq.version = SKY_SOFTWARE_VERSION; // skyhook client library version
      rq.ap_count = n & 0xFF; // set the number of scanned access points
  
      rq.aps = aps; // assign aps
      // in this demo we are not using cell, ble or gps
      // zero counts
      uint8_t tmp_ip[4];
      uint8_t * localip = tmp_ip;
      localip[0] = WiFi.localIP()[0];
      localip[1] = WiFi.localIP()[1];
      localip[2] = WiFi.localIP()[2];
      localip[3] = WiFi.localIP()[3];
      rq.ble_count = 0;
      rq.cell_count = 0;
      rq.gps_count = 0;
      rq.ip_addr = localip;
      rq.ip_type = DATA_TYPE_IPV4;
      rq.ip_count = 1;
      rq.mac_count = 1;

      Serial.println("\n########### Location Request ###########");

      Serial.println("Protocol: " + String(rq.header.version));
      Serial.println("Num APs: " + String(rq.ap_count));
      Serial.println(sizeof(buff));
      int cnt = sky_encode_req_bin(buff, SKY_PROT_BUFF_LEN, &rq);
  
      if (cnt == -1){
          Serial.println("failed to encode request");
          return;
      }

      Serial.println("ENCODING DONE");
  
      /* encrypt buffer, use hardware encryption when available */
      Serial.println(cnt);
      print_buff(buff, cnt);
      Serial.println(cnt - sizeof(sky_rq_header_t));
      int r = sky_aes_encrypt(buff + sizeof(sky_rq_header_t), cnt - sizeof(sky_rq_header_t) - sizeof(sky_checksum_t), key.aes_key, buff + sizeof(sky_rq_header_t) - sizeof(rq.header.iv));
  
      if (r == -1){
          Serial.println("failed to encrypt");
          return;
      }
  
      // close any connection
      client.stop();
  
      Serial.print("connecting to ");
      Serial.print(SKYHOOK_ELG_SERVER_URL);
      Serial.print(":");
      Serial.println(SKYHOOK_ELG_SERVER_PORT);

      // on failure to connect to elg server
      if (!client.connect(SKYHOOK_ELG_SERVER_URL, SKYHOOK_ELG_SERVER_PORT))
      {
          Serial.println("connection failed");
          oled.clearDisplay();
          device.update_oled();
          print_to_oled("connection failed", "retrying...");
          oled.display();
          unsigned long now = millis();

          // "delay" for a second
          while(true){
            yield();
            if(now - millis() > 1000){
              break;
            }
            if(state.update()){return;}
          }
          return;
      }
  
      size_t wcnt = client.write((const uint8_t *)buff, (size_t)cnt);
      Serial.print("sent:");
      Serial.println(wcnt);
      sent = true;
      WiFi.scanDelete();
      Serial.println("########################################\n");
  }
  bool rx(){
    uint8_t * buff = NULL;
    SKY_LOCAL_BYTE_BUFF_32(buff,SKY_PROT_BUFF_LEN);

    int n = client.available();
    while(n = client.available()){
      // check for button interrupt
      if(state.update()) return false;

      
      // trim to buff size
      if (n > SKY_PROT_BUFF_LEN){
          n = SKY_PROT_BUFF_LEN;
      }
      Serial.println("\n########### Location Response ###########");
      //Serial.println(buff);
      n = client.read(buff, n);
      Serial.print("read bytes: ");
      Serial.println(n);

      memset(&resp.location_ext, 0, sizeof(resp.location_ext)); // clear the values
      resp.key = key; // assign decryption key

      if (sky_aes_decrypt(buff + sizeof(sky_rsp_header_t), n - sizeof(sky_rsp_header_t) - sizeof(sky_checksum_t), key.aes_key, buff + sizeof(sky_rsp_header_t) - sizeof(resp.header.iv)) != 0){
          Serial.println("failed to decrypt response");
          return false;
      }

      print_buff(buff, n);

      int res = sky_decode_resp_bin(buff, SKY_PROT_BUFF_LEN, n, &resp);

      if (res == -1){
          Serial.println("failed to decode response");
          return false;
      }

      print_location_resp(&resp);
      sent = false;
      return true;
    }
    return false;
  }
  // ONLY FOR DEBUGGING IN SERIAL
  void print_location_resp(struct location_rsp_t *cr)
  {
    Serial.println();
    Serial.print("timestamp: ");

    uint64_t timestamp = 0;
    strncpy((char *)&timestamp, (const char *)cr->payload_ext.payload.timestamp, sizeof(cr->payload_ext.payload.timestamp));
    print64(timestamp);
    Serial.println();

/*
    char str[100];
    sprintf(str, "%" PRIu64, cr->timestamp);
    Serial.println(str);
*/
    Serial.print("protocol: "); Serial.println(cr->header.version);
    //Serial.print("server version: "); Serial.println(cr->version);
    Serial.print("payload type no: "); Serial.println(cr->payload_ext.payload.type);
    
    // http codes
    // if (cr->payload_ext.payload.type < HTTP_UNKNOWN && cr->payload_ext.payload.type >= HTTP_200)
    // {
    //     int err;
    //     if (cr->payload_ext.payload.type > HTTP_505) err = HTTP_UNKNOWN;
    //     else if (cr->payload_ext.payload.type >= HTTP_500) err = cr->payload_ext.payload.type - HTTP_500 + 500;
    //     else if (cr->payload_ext.payload.type > HTTP_417) err = HTTP_UNKNOWN;
    //     else if (cr->payload_ext.payload.type >= HTTP_400) err = cr->payload_ext.payload.type - HTTP_400 + 400;
    //     else if (cr->payload_ext.payload.type > HTTP_307) err = HTTP_UNKNOWN;
    //     else if (cr->payload_ext.payload.type >= HTTP_300) err = cr->payload_ext.payload.type - HTTP_300 + 300;
    //     else if (cr->payload_ext.payload.type > HTTP_206) err = HTTP_UNKNOWN;
    //     else if (cr->payload_ext.payload.type >= HTTP_200) err = cr->payload_ext.payload.type - HTTP_200 + 200;
    //     else err = HTTP_UNKNOWN;

    //     Serial.print("HTTP "); Serial.println(err);
    // }
    // else
    // {
        switch (cr->payload_ext.payload.type)
        {
            case LOCATION_RQ_SUCCESS: Serial.println("LOCATION_RQ_SUCCESS"); break;
            case LOCATION_RQ_ADDR_SUCCESS: Serial.println("LOCATION_RQ_ADDR_SUCCESS"); break;
            case PROBE_REQUEST_SUCCESS: Serial.println("PROBE_REQUEST_SUCCESS"); break;
            case LOCATION_RQ_ERROR: Serial.println("LOCATION_RQ_ERROR"); break;
            case LOCATION_GATEWAY_ERROR: Serial.println("LOCATION_GATEWAY_ERROR"); break;
            case LOCATION_API_ERROR: Serial.println("LOCATION_API_ERROR"); break;
            case LOCATION_UNKNOWN: Serial.println("LOCATION_UNKNOWN"); break;
            case LOCATION_UNABLE_TO_DETERMINE: Serial.println("LOCATION_UNABLE_TO_DETERMINE"); break;
        }
    // }

    if (cr->payload_ext.payload.type != LOCATION_RQ_SUCCESS &&
        cr->payload_ext.payload.type != LOCATION_RQ_ADDR_SUCCESS) return;

    Serial.println("LOCATION_RQ_SUCCESS");
    Serial.print("latitude: "); Serial.println(cr->location.lat, 6);
    Serial.print("longitude: "); Serial.println(cr->location.lon, 6);
    Serial.print("hpe: "); Serial.println(cr->location.hpe);
    Serial.print("distance_to_point: "); Serial.println(cr->location.distance_to_point);
    
    if (cr->payload_ext.payload.type == LOCATION_RQ_ADDR_SUCCESS)
    {
        Serial.println("LOCATION_RQ_ADDR_SUCCESS");
        Serial.print("street num: "); print_s(cr->location_ext.street_num, cr->location_ext.street_num_len);
        Serial.print("address: "); print_s(cr->location_ext.address, cr->location_ext.address_len);
        Serial.print("city: "); print_s(cr->location_ext.city, cr->location_ext.city_len);
        Serial.print("state: "); print_s(cr->location_ext.state, cr->location_ext.state_len);
        Serial.print("state code: "); print_s(cr->location_ext.state_code, cr->location_ext.state_code_len);
        Serial.print("postal code: "); print_s(cr->location_ext.postal_code, cr->location_ext.postal_code_len);
        Serial.print("county: "); print_s(cr->location_ext.county, cr->location_ext.county_len);
        Serial.print("country: "); print_s(cr->location_ext.country, cr->location_ext.country_len);
        Serial.print("country code: "); print_s(cr->location_ext.country_code, cr->location_ext.country_code_len);
        Serial.print("metro1: "); print_s(cr->location_ext.metro1, cr->location_ext.metro1_len);
        Serial.print("metro2: "); print_s(cr->location_ext.metro2, cr->location_ext.metro2_len);
        Serial.print("ip: "); print_ip(cr->location_ext.ip_addr, cr->location_ext.ip_type);
        Serial.println("#########################################\n");
    }
  }
  // ONLY FOR DEBUGGING IN SERIAL
  void print_s(char *buff, int len)
  {
      int i;
      for (i = 0; i < len; i++)
      {
          Serial.print(buff[i]);
      }
  
      Serial.println();
  }
  // ONLY FOR DEBUGGING IN SERIAL
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
              Serial.print(ip[i+1], HEX);
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

  // handles elg request and response and displays on the oled
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
      else{
        if(now - rxTimer > WIFI_RX_WAIT_TIME){
          if(now - rxTimer < SOCKET_TIMEOUT){
            if(rx()){
              rxTimer = now;
              // SERIAL DEBUGGING
              print_location_oled();
              check_time = 0;
            }
          }
          else{
            Serial.println("Socket Timeout "+String(now - rxTimer));
            client.stop();
            sent = false;
          }
        }
      }
    }
    else{
      oled.clearMsgArea();
      print_to_oled("Wifi Disconnected","");
      device.handle();
    }
  }

  // function that will return a single location response in a form of a json
  void location_json(){
    String error = "";
    while(true){
      unsigned long now = millis();
      if(WiFi.status() == WL_CONNECTED){
        if(!sent){
          if(now-txTimer > scan_frq){
            scan();
            txTimer = now;
            rxTimer = now;
          }
        }
        else{
          if(now - rxTimer > WIFI_RX_WAIT_TIME){
            while(!(now - rxTimer < SOCKET_TIMEOUT + WIFI_RX_WAIT_TIME)){
              if(rx()){
                if(get_error(error)){
                  Serial.println(error);
                  server.send(200,"application/json","{\"error\": \""+error+"\"}");
                  print_to_oled("Location error",error);
                }
                rxTimer = now;
                check_time = 0;
                String address = "";
                if(reverse_geo)
                {
                  int loc_req_arr[5]={resp.location_ext.street_num_len,resp.location_ext.address_len,resp.location_ext.metro1_len,resp.location_ext.state_code_len,resp.location_ext.postal_code_len};
                  char buf[get_max(loc_req_arr,5)+1];
                  address = "\"";
                  snprintf(buf, resp.location_ext.street_num_len+1, "%s", resp.location_ext.street_num);
                  address += String(buf) + " ";
                  snprintf(buf, resp.location_ext.address_len+1, "%s", resp.location_ext.address);
                  address += String(buf) + ", ";
                  snprintf(buf, resp.location_ext.metro1_len+1, "%s", resp.location_ext.metro1);
                  address += String(buf) + ", ";
                  snprintf(buf, resp.location_ext.state_code_len+1, "%s", resp.location_ext.state_code);
                  address += String(buf) + ", ";
                  snprintf(buf, resp.location_ext.postal_code_len+1, "%s", resp.location_ext.postal_code);
                  address += String(buf)+"\"";
                }
                else{
                  address = "\"\"";
                }
                server.send(200,"application/json","{\"LAT\": "+String(resp.location.lat,5)+", \"LON\":"+String(resp.location.lon,5)+",\"HPE\":"+resp.location.hpe+",\"reverse_geo\":"+address+"}");
                return;
              }
              else{
                sent = false;
                server.send(200,"application/json","{\"error\":\"No Response\"}");
                return;
              }
            }
          }
        }
      }
      else{
        server.send(200,"application/json","{\"error\":\"WiFi Disconnected\"}");
      }
      yield();
    }
  }
};

ClientWiFiWrapper client_req;

void connect_to_wifi() {
  Serial.print("Attempting to connect to know aps...");
  print_to_oled("Connecting to APs","");
  // tell device to connect to saved AP's in AP.json
  client_req.conn_known_ap();
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!");
    print_to_oled("Success: " + WiFi.SSID(),"");
  }
  else{
    Serial.println("Unable to connect to known AP's");
    print_to_oled("Unable to connect to known AP's","");
  }
  yield();
}

// start state of the device to be in Client mode on bootup
// Change to start in Client Mode.
void setup() {
/* Uncomment the next line to disable watchdog timer for debugging */
//  ESP.wdtDisable();
/* Uncomment the next line to make the RST pin/button a soft on/off button */
//  determine_on_state();

//  WiFi.setAutoReconnect(true);
//  WiFi.setAutoConnect(true);

  // Begin Serial output
  if(DEBUG){
    Serial.begin(115200);
    Serial.setDebugOutput(true);
  }
  
  optimistic_yield(100);
  // Begin ESP8266 File management system
  SPIFFS.begin();
  optimistic_yield(100);

  gauge.reset();
  optimistic_yield(100);
  gauge.setAlertThreshold(ALERT_THRESHOLD);
  Serial.println(String("Alert Threshold is set to ") + gauge.getAlertThreshold() + '%');

  // preferences.json is loaded and boolean values are set
  load_config();
  // initialize OLED
  oled.init();
  oled.clearDisplay();
  // clear RSSI
  oled.setRSSI(0);
  // display Logo for Skyhook
  oled.drawBitmap(0, 0, skyhook_logo, 128, 32, WHITE);
  oled.display();
  // config WiFi
  WiFi.mode(WIFI_AP_STA);
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);
  // display logo for 4 seconds with no interrupts but allow device to run processes
  delay(4000);
  oled.clearDisplay();
  oled.setConnected(INITIAL_STARTUP_STATE);
  oled.refreshIcons();

  // station mode allows both client and AP mode
  Serial.println();
  Serial.println("Configuring access point...");
  
  // set ssid and password
  WiFi.softAP(ssid, password);
  WiFi.softAPmacAddress(mac);
  yield();
  // connect to known WiFi
  connect_to_wifi();
  yield();

  // handles API like calls to the device
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
  Serial.println("Initializing Server");
  yield();

  device.handle();

  Serial.println("Saved Networks:");
  print_saved_networks();
  Serial.println();
  Serial.println("Saved Preferences:");
  print_saved_preferences();
  Serial.println();
  
  Serial.println("HTTP server started");
  Serial.println("Open "+ WiFi.softAPIP().toString()+" in your browser\n");
  device.set_state_settings();
  if(device.getDeviceState() == AP){
    print_to_oled("Open in browswer:", WiFi.softAPIP().toString());
  }
}

void loop() {
  // make sure WiFi connected
  if(WiFi.status() != WL_CONNECTED){
    connect_to_wifi();
  }
  // handle differently depending on device state
  if(device.getDeviceState() == AP){
    server.handleClient();
    device.handle();
  }
  else{
    client_req.handle();
  }
  state.update();
  yield();
}

void load_config(){
  String config_json;
  if (!file_to_string("/resources/preferences.json","r",config_json)) {
    Serial.println("Config not found!");
    print_to_oled("Config not found","setting default values");
    scan_frq = SCAN_DEFAULT_FRQ;
    HPE = HPE_DEFAULT_VAL;
    reverse_geo = REVERSE_GEO_DEFAULT_VAL;
  }
  
  DynamicJsonBuffer config_obj_buf;
  JsonObject& config_obj = config_obj_buf.parseObject(config_json);

  // set values to their corresponding values in preference.json
  scan_frq = config_obj["scan_freq"];
  HPE = config_obj["HPE"];
  reverse_geo = config_obj["reverse_geo"];
}

void change_device_state(){
  device.change_state();
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

bool string_to_bool(String input){
  input.toLowerCase();
  if(input == "true"){
    return true;
  }
  else{
    return false;
  }
}

bool file_to_string(String path, const char* type, String& ret_buf){
  if (SPIFFS.exists(path)) {
      File a = SPIFFS.open(path, type);
      while(a.available()){
        ret_buf += (char)a.read();
      }
      a.close();
      return true;
  }
  return false;
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
    String error = "";
    if(!page1_done){
      if (get_error(error)){
        oled.clearDisplay();
        device.update_oled();
        oled.setCursor(0,8);
        oled.println("Unable to determine  location");
      }
      else{
        oled.clearDisplay();
        device.update_oled();
        oled.setCursor(0,0);
        oled.println("INFO:");
        oled.println("LAT: " + String(resp.location.lat, 5));
        oled.println("LON: " + String(resp.location.lon, 5));
        if(HPE){
          oled.println("HPE: " + String(resp.location.hpe, 5));
        }
      }
      oled.display();
      page1_done = true;
    }
    if(now - start_time > page1_display_timer && !page2_done){
      if(resp.payload_ext.payload.type == LOCATION_RQ_ADDR){
        oled.clearDisplay();
        device.update_oled();
        oled.setCursor(0,0);
        oled.println("ADDRESS:");
        int loc_req_arr[5]={resp.location_ext.street_num_len,resp.location_ext.address_len,resp.location_ext.metro1_len,resp.location_ext.state_code_len,resp.location_ext.postal_code_len};
        char buff[get_max(loc_req_arr,5)+1];
        
        snprintf(buff, resp.location_ext.street_num_len+1, "%s", resp.location_ext.street_num);
        oled.print(buff);
        oled.write(' ');

        snprintf(buff, resp.location_ext.address_len+1, "%s", resp.location_ext.address);
        //oled.print(String(resp.location_ex.address));
        oled.print(buff);
        oled.write(',');
        oled.write(' ');

        snprintf(buff, resp.location_ext.metro1_len+1, "%s", resp.location_ext.metro1);
        //oled.print(String(resp.location_ex.metro1));
        oled.print(buff);
        oled.write(',');
        oled.write(' ');

        snprintf(buff, resp.location_ext.state_code_len+1, "%s", resp.location_ext.state_code);
        //oled.print(String(resp.location_ex.state_code));
        oled.print(buff);
        oled.write(',');
        oled.write(' ');
        
        snprintf(buff, resp.location_ext.postal_code_len+1, "%s", resp.location_ext.postal_code);
        oled.println(buff);
      }
      else{
        oled.clearDisplay();
        oled.setCursor(0,8);
        oled.println("Unable to determine location");
      }
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

void handleRoot() {
  Serial.println("Requesting " + server.uri());

  File f;
  f = SPIFFS.open("/index.html", "r");
  optimistic_yield(200);
  if (!f) {
    Serial.println(server.uri() + " does not exist");
  }
  if (server.streamFile(f, "text/html") != f.size()) {
    Serial.println("Error");
  }
  f.close();
}

void handleResources() {
  Serial.println("Requesting: " + server.uri());
  // begin file mangament
  String path = server.uri();
  String dataType = "";
  if (path.endsWith("/")) path += "index.html";

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
  else dataType = "text/plain";
  File dataFile = SPIFFS.open(path, "r");
  if(!dataFile){
    Serial.println(path+" not found!");
    server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
  }
  else{ 
    if (server.streamFile(dataFile, dataType) != dataFile.size()) {
      Serial.println("Error");
    }
  }
  dataFile.close();
}

void handleScan() {
  Serial.println("Scanning Networks");
  print_to_oled("Scanning Networks", "");
  int n = WiFi.scanNetworks();
  DynamicJsonBuffer scan_obj_buf;
  JsonObject& scan_obj = scan_obj_buf.createObject();

  for (int i = 0; i < n; i++) {
    
    // handle button interrupt
    if(state.update()) return;
    if(!scan_obj[WiFi.SSID(i)].success()){
      DynamicJsonBuffer scan_info_buf;
      
      JsonObject& scan_info = scan_obj.createNestedObject(WiFi.SSID(i));
      JsonObject& id_info = scan_info.createNestedObject(WiFi.BSSIDstr(i));
  
      insert_bssid_info(id_info,i);
    }
    else{
      JsonObject& thing = scan_obj[WiFi.SSID(i)];
      JsonObject& id_info = thing.createNestedObject(WiFi.BSSIDstr(i));
  
      insert_bssid_info(id_info,i);
    }
  }
  scan_obj.prettyPrintTo(Serial);
  main_wifi.send_json_response(scan_obj);
  Serial.println("JSON Sent");
  WiFi.scanDelete();
  oled.clearMsgArea();
}

void insert_bssid_info(JsonObject& info, int index){
  info["rssi"] = WiFi.RSSI(index);
  info["channel"] = WiFi.channel(index);
  info["rssi"] = WiFi.RSSI(index);
  info["encrypt"] = encryptionTypeStr(WiFi.encryptionType(index));
  info["hidden"] = WiFi.isHidden(index);
}

void handleChangeAP() {
  Serial.println("User is trying to change AP");
  if (server.hasArg("ssid") && server.hasArg("password")) {
    Serial.println("SSID: " + server.arg("ssid"));
    Serial.println("Password: " + server.arg("password"));
    server.sendHeader("Refresh", "10; url=/");
    // TODO: handle error
    server.send(200);
  }
  else{
    server.send(400);
    return;
  }

  print_to_oled("Connecting to: " + server.arg("ssid"), "");

  // If connection successful
  if(main_wifi.connect_to(server.arg("ssid"), server.arg("password"))){
    Serial.println("Connected to WiFi");
    if (!main_wifi.save_connected_network(server.arg("password"))) {
      Serial.println("Couldn't save AP to database");
      print_to_oled("Failed to save AP Info","");
    }
  }
  else{
    Serial.println("Failed to Connect to AP");
    print_to_oled("Couldn't connect to AP","");
    return;
  }
}

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
  main_wifi.send_json_response(wifistatus_obj);
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

void handleChangePreferences(){
  Serial.println("User is trying to change Preferences");
  String preferences;
  if (server.hasArg("HPE") && server.hasArg("reverse_geo") && server.hasArg("scan_freq")) {
    String HPE_user = server.arg("HPE");
    if (!file_to_string("/resources/preferences.json","r",preferences)) {
      preferences = "{}";
    }
    Serial.println("before");
    Serial.println(preferences);
    
    DynamicJsonBuffer pref_obj_buf;
    JsonObject& pref_obj = pref_obj_buf.parseObject(preferences);
    pref_obj["HPE"] = string_to_bool(server.arg("HPE"));
    pref_obj["reverse_geo"] = string_to_bool(server.arg("reverse_geo"));
    int scan_freq_input = server.arg("scan_freq").toInt();
    if(scan_freq_input < 200){
      scan_freq_input = SCAN_DEFAULT_FRQ;
    }
    pref_obj["scan_freq"] = scan_freq_input;
    pref_obj["realm_id"] = server.arg("realm_id").toInt();
    pref_obj["aes_key"] = server.arg("aes_key");

    if (!SPIFFS.exists("/resources/preferencesTmp.json")) {
      SPIFFS.remove("/resources/preferencesTmp.json");
    }
  
    File b = SPIFFS.open("/resources/preferencesTmp.json", "w");
    // ERROR: file couldn't be open or created
    if (!b) {
      server.send(200,"application/json","{\"error\":\"No Preferences Json\"}");
      return;
    }
    // write to file
    pref_obj.printTo(b);
    b.close();

    // update global "sky_key_t key"
    key.userid = pref_obj["realm_id"];
    memset(key.aes_key, 0, sizeof(key.aes_key));
    hex2bin((const char *)pref_obj["aes_key"], strlen(pref_obj["aes_key"]), key.aes_key, sizeof(key.aes_key));

    Serial.println("after");
    pref_obj.prettyPrintTo(Serial);
    Serial.println();
    // delete the old AP list and update the new one to have the same name
    SPIFFS.remove("/resources/preferences.json");
    SPIFFS.rename("/resources/preferencesTmp.json", "/resources/preferences.json");
  
    // double checks that the JSON exists
    if (SPIFFS.exists("/resources/preferences.json")) {
      Serial.println("Preferences Change Successful");
      load_config();
      server.send(200);
    }
    else {
      server.send(200,"application/json","{\"error\":\"No preferences Json after rename\"}");
    }
  }
  else{
    server.send(200,"application/json","{\"error\":\"Incomplete Request\"}");
    Serial.println("incomplete request");
  }
}

void handleLocation(){
  client_req.location_json();
}

void handleNotFound() {
  server.send(404, "text/html", "<head></head><h1>404 Not Found</h1>");
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

bool get_error(String& error){
  if (resp.payload_ext.payload.type != LOCATION_RQ && resp.payload_ext.payload.type != LOCATION_RQ_ADDR){
      switch (resp.payload_ext.payload.type)
      {
            case LOCATION_RQ_SUCCESS: Serial.println("LOCATION_RQ_SUCCESS"); break;
            case LOCATION_RQ_ADDR_SUCCESS: Serial.println("LOCATION_RQ_ADDR_SUCCESS"); break;
            case PROBE_REQUEST_SUCCESS: Serial.println("PROBE_REQUEST_SUCCESS"); break;
            case LOCATION_RQ_ERROR: Serial.println("LOCATION_RQ_ERROR"); break;
            case LOCATION_GATEWAY_ERROR: Serial.println("LOCATION_GATEWAY_ERROR"); break;
            case LOCATION_API_ERROR: Serial.println("LOCATION_API_ERROR"); break;
            case LOCATION_UNKNOWN: Serial.println("LOCATION_UNKNOWN"); break;
            case LOCATION_UNABLE_TO_DETERMINE: Serial.println("LOCATION_UNABLE_TO_DETERMINE"); break;
      }
      return true;
  }
    return false;
}

int get_max(int buf[], int len){
  int max = 0;
  for(int i = 0; i < len; i++){
    if(buf[i] > max){
      max = buf[i];
    }
  }
  return max;
}

void print64(uint64_t value){
    const int NUM_DIGITS = log10(value) + 1;

    char sz[NUM_DIGITS + 1];
    
    sz[NUM_DIGITS] =  0;
    for ( size_t i = NUM_DIGITS; i--; value /= 10)
    {
        sz[i] = '0' + (value % 10);
    }

    Serial.print(sz);
}

// DEBUGGING
void print_saved_networks() {
  String APjson;
  if (!file_to_string("/resources/AP.json","r",APjson)) {
    return;
  }
  DynamicJsonBuffer bssid_obj_buf;
  JsonObject& bssid_obj = bssid_obj_buf.parseObject(APjson);
  bssid_obj.prettyPrintTo(Serial);
  Serial.println();
}

// DEBUGGING
void print_saved_preferences(){
  String pref;
  if (!file_to_string("/resources/preferences.json","r",pref)) {
    return;
  }
  DynamicJsonBuffer bssid_obj_buf;
  JsonObject& bssid_obj = bssid_obj_buf.parseObject(pref);
  bssid_obj.prettyPrintTo(Serial);
  Serial.println();
}


