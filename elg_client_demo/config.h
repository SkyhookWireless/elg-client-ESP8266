/************************************************
* Authors: Istvan Sleder and Marwan Kallal
* 
* Company: Skyhook Wireless
*
************************************************/
/* url to skyhook ELG server */
const char *SKYHOOK_ELG_SERVER_URL = "elg.skyhookwireless.com";
/* Skyhook ELG server port */
#define SKYHOOK_ELG_SERVER_PORT 9755

/* userid provided by Skyhook */
/* replace this with yours */
#define USERID 12345

/*  AES key provided by Skyhook */
/* replace this with yours */
/* store the key in a secure area */
#define AES_KEY {0x02,0x43,0x21,0xA2,0x7D,0x72,0x0F,0x01,0x21,0x12,0x02,0x12,0x02,0x12,0x02,0x21}

// access point ap name
const char *AP_SSID = "Skyhook ELG";
// access point port number
#define AP_PORT 80
// wifi rx, tx buffer
#define BUFF_SIZE 1024
// max number of access point (mem alloc)
#define MAX_AP_COUNT 50
// wait for packet reception
#define WIFI_RX_WAIT_TIME 2000 // ms

// user button
#define AP              1
#define CLIENT          0

#define BUTTON_DEBOUNCE 175 // ms
#define MODE_SWITCH_TIME 500000 // us

// uart baud rate
#define SERIAL_BAUD_RATE 115200

#define SCAN_DEFAULT_FRQ 2000 // ms
#define DEVICE_UPDATE_RATE 1000
#define MAX_AUTOJOIN_APS 5
#define INITIAL_STARTUP_STATE 1

// micro OLED sparkfun
// #define OLED_RESET
