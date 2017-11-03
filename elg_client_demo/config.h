/************************************************
* Authors: Istvan Sleder and Marwan Kallal
* 
* Company: Skyhook Wireless
*
************************************************/
/* url to skyhook ELG server useapi-dev.skyhookwireless.com wapi-stage2.skyhookwireless.com*/
//elg.skyhookwireless.com
const char *SKYHOOK_ELG_SERVER_URL = "elg.skyhook.com";
/* Skyhook ELG server port */
#define SKYHOOK_ELG_SERVER_PORT 9755

// access point ap name
const char *AP_SSID = "Skyhook ELG";
// access point port number
#define AP_PORT 80
// wait for packet reception
#define WIFI_RX_WAIT_TIME 10000 // ms

#define SOCKET_TIMEOUT 10000 // ms

// user button
#define AP              1
#define CLIENT          0

#define BUTTON_DEBOUNCE 175 // ms
#define MODE_SWITCH_TIME 500000 // us

// uart baud rate
#define SERIAL_BAUD_RATE 115200

// intially defines scan frequency initally in case config.json isn't loaded
#define SCAN_DEFAULT_FRQ 2000 // ms
#define HPE_DEFAULT_VAL true
#define REVERSE_GEO_DEFAULT_VAL true

// defines how frequently the device refreshes voltage readings, rssi readings, etc
#define DEVICE_UPDATE_RATE 1000

// max number of successfully connected AP's that are saved into AP.json
#define MAX_AUTOJOIN_APS 5

// defines the inital state on startup
#define INITIAL_STARTUP_STATE CLIENT
#define DEBUG 1
#define ALERT_THRESHOLD 15 // %
// micro OLED sparkfun
// #define OLED_RESET
