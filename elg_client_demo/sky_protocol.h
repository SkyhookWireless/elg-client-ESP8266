/************************************************
 * Authors: Liang Zhao and Ted Boinske
 * 
 * Company: Skyhook
 *
 ************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SKY_PROTOCOL_H
#define SKY_PROTOCOL_H

#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>



/*************************************************************************
 *
 * Skyhook Macros and Types for ELGv2 Protocol
 *
 *************************************************************************/

#define SKY_PROTOCOL_VERSION    1

#define URL_FORMAT              "elg://host:port/"

#define HOST_SIZE               512
#define PORT_SIZE               6 // max port# is 65535
#define URL_SIZE                sizeof(URL_FORMAT) + HOST_SIZE + PORT_SIZE
#define AUTH_SIZE               512

#define MAC_SIZE                6
#define IPV4_SIZE               4
#define IPV6_SIZE               16

#define MAX_MACS                2   // max # of mac addresses
#define MAX_IPS                 2   // max # of ip addresses

#define MAX_APS                 100 // max # of access points
#define MAX_GPSS                2   // max # of gps
#define MAX_CELLS               7   // max # of cells
#define MAX_BLES                5   // max # of blue tooth

// max # of bytes for request buffer
#define SKY_PROT_RQ_BUFF_LEN                                                 \
    sizeof(sky_rq_header_t) + sizeof(sky_payload_t) + sizeof(sky_checksum_t) \
    + (sizeof(sky_entry_t) + MAX_MACS * MAC_SIZE)                            \
    + (sizeof(sky_entry_t) + MAX_IPS * IPV6_SIZE)                            \
    + (sizeof(sky_entry_t) + MAX_APS * sizeof(struct ap_t))                  \
    + (sizeof(sky_entry_t) + MAX_GPSS * sizeof(struct gps_t))                \
    + (sizeof(sky_entry_t) + MAX_CELLS * sizeof(union cell_t))               \
    + (sizeof(sky_entry_t) + MAX_BLES * sizeof(struct ble_t))

// max # of bytes for response buffer
#define SKY_PROT_RSP_BUFF_LEN                                                 \
    sizeof(sky_rsp_header_t) + sizeof(sky_payload_t) + sizeof(sky_checksum_t) \
    + sizeof(struct location_t) + sizeof(struct location_ext_t)               \
    + 1024 // the char array of full address

// max # of bytes for both request and response buffer
#define SKY_PROT_BUFF_LEN                                                     \
                            ((SKY_PROT_RQ_BUFF_LEN > SKY_PROT_RSP_BUFF_LEN) ? \
                            SKY_PROT_RQ_BUFF_LEN : SKY_PROT_RSP_BUFF_LEN)

#ifndef ENOBUFS
    #define ENOBUFS (ENOMEM)
#endif

// get a local (uint8_t *) buffer with size s and the starting memory address
// being aligned at uint32_t boundary.
#define SKY_LOCAL_BYTE_BUFF_32(b,s)                                           \
                            uint32_t sky____local_buffer____sky[(s)>>2];      \
                            assert(sizeof(*b) == sizeof(uint8_t));            \
                            (b) = (uint8_t *)sky____local_buffer____sky;

#ifndef _BYTESWAP_H // defined in <byteswap.h>
    #define __sky_bswap_16(x)                                                 \
         ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)))
    #define __sky_bswap_32(x)                                                 \
         ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >>  8)             \
        | (((x) & 0x0000ff00) <<  8) | (((x) & 0x000000ff) << 24))
    #define __sky_bswap_64(x)                                                 \
         ((((x) & 0xff00000000000000ull) >> 56)                               \
        | (((x) & 0x00ff000000000000ull) >> 40)                               \
        | (((x) & 0x0000ff0000000000ull) >> 24)                               \
        | (((x) & 0x000000ff00000000ull) >> 8)                                \
        | (((x) & 0x00000000ff000000ull) << 8)                                \
        | (((x) & 0x0000000000ff0000ull) << 24)                               \
        | (((x) & 0x000000000000ff00ull) << 40)                               \
        | (((x) & 0x00000000000000ffull) << 56))
#else
    #define __sky_bswap_16(x)       __bswap_16(x)
    #define __sky_bswap_32(x)       __bswap_32(x)
    #define __sky_bswap_64(x)       __bswap_64(x)
#endif

#ifdef __BIG_ENDIAN__ // defined in <endian.h> by GNU C compilers
    #define SKY_ENDIAN_SWAP(x)                                                \
                           ({switch(sizeof(x)) {                              \
                             case (sizeof(uint8_t)):                          \
                                 break;                                       \
                             case (sizeof(uint16_t)):                         \
                                 (x) = __sky_bswap_16(x);                     \
                                 break;                                       \
                             case (sizeof(uint32_t)):                         \
                                 (x) = __sky_bswap_32(x);                     \
                                 break;                                       \
                             case (sizeof(uint64_t)):                         \
                                 (x) = __sky_bswap_64(x);                     \
                                 break;                                       \
                             default:                                         \
                                 perror("NOT C primitive types!");            \
                                 assert(false);                               \
                                 break;                                       \
                             }})
#else
    #define SKY_ENDIAN_SWAP(x) // do nothing
#endif


// stored in one byte
enum SKY_DATA_TYPE {
    DATA_TYPE_PAD = 0,      // padding byte
    DATA_TYPE_AP = 1,       // access point
    DATA_TYPE_GPS,          // gps
    DATA_TYPE_GSM,          // cell gsm
    DATA_TYPE_CDMA,         // cell cdma
    DATA_TYPE_UMTS,         // cell umts
    DATA_TYPE_LTE,          // cell lte
    DATA_TYPE_BLE,          // bluetooth

    DATA_TYPE_LAT_LON,      // lat and lon
    DATA_TYPE_STREET_NUM,
    DATA_TYPE_ADDRESS,
    DATA_TYPE_CITY,
    DATA_TYPE_STATE,
    DATA_TYPE_STATE_CODE,
    DATA_TYPE_METRO1,
    DATA_TYPE_METRO2,
    DATA_TYPE_POSTAL_CODE,
    DATA_TYPE_COUNTY,
    DATA_TYPE_COUNTRY,
    DATA_TYPE_COUNTRY_CODE,

    DATA_TYPE_IPV4,         // ipv4 address
    DATA_TYPE_IPV6,         // ipv6 address
    DATA_TYPE_MAC,          // device MAC address
};

// request payload types
enum SKY_RQ_PAYLOAD_TYPE {
    REQ_PAYLOAD_TYPE_NONE = 0,  // initialization value

    LOCATION_RQ,                // location request
    LOCATION_RQ_ADDR,           // location request full
    PROBE_REQUEST,              // probe test
};

// response payload types
enum SKY_RSP_PAYLOAD_TYPE {
    RSP_PAYLOAD_TYPE_NONE = 0,  // initialization value

    // success codes
    LOCATION_RQ_SUCCESS,        // lat+lon success
    LOCATION_RQ_ADDR_SUCCESS,   // full address success
    PROBE_REQUEST_SUCCESS,      // probe success

    // error codes
    LOCATION_RQ_ERROR = 10,      // client domain errors
    LOCATION_GATEWAY_ERROR,      // elg server domain errors
    LOCATION_API_ERROR,          // api server domain errors
    LOCATION_UNKNOWN,            // do not know which domain errors

    // detailed client domain error codes
    LOCATION_UNABLE_TO_DETERMINE = 20,// api-server is unable to determine the client
                                      // location by the given client data.
};

// internal error codes
enum SKY_STATUS {
    SKY_OK = 0,
    ZLOG_INIT_PERM,
    ZLOG_INIT_ERR,
    LOAD_CONFIG_FAILED,
    API_URL_UNKNOWN,
    RELAY_URL_UNKNOWN,
    LOAD_KEYS_FAILED,
    BAD_KEY,
    CREATE_THREAD_FAILED,
    SETSOCKOPT_FAILED,
    SOCKET_OPEN_FAILED,
    SOCKET_CONN_FAILED,
    SOCKET_BIND_FAILED,
    SOCKET_LISTEN_FAILED,
    SOCKET_ACCEPT_FAILED,
    SOCKET_RECV_FAILED,
    SOCKET_WRITE_FAILED,
    SOCKET_TIMEOUT_FAILED,
    MSG_TOO_SHORT,
    SEND_PROBE_FAILED,
    SEND_UDF_PROT_FAILED,
    SENDTO_FAILED,
    DECRYPT_BIN_FAILED,
    ENCODE_XML_FAILED,
    DECODE_BIN_FAILED,
    ENCODE_BIN_FAILED,
    ENCRYPT_BIN_FAILED,
    DECODE_XML_FAILED,
    CREATE_META_FAILED,
    ARRAY_SIZE_TOO_SMALL,
    ERROR_XML_MSG,

    /* HTTP response codes >= 100 */
    /* http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html */
};

//
// protocol header, payload and checksum data types
//

// Note: For multi-byte integers, the server code runs on little-endian machines.
//       As the protocol requires little-endianness, server code does not need to
//       concern about byte ordering.
typedef struct {
    uint8_t version;           // protocol version
    uint8_t unused;            // padding byte
    uint16_t payload_length;   // payload length
    uint32_t partner_id;       // user id
    uint8_t iv[16];            // initialization vector
} sky_rq_header_t;

typedef struct {
    uint8_t version;           // protocol version
    uint8_t unused;            // padding byte
    uint16_t payload_length;   // payload length
    uint8_t iv[16];            // initialization vector
} sky_rsp_header_t;

typedef struct {
    uint8_t data_type;         // data type enum (i.e. SkyDataType)
    uint8_t data_type_count;   // data type count
} sky_entry_t;

// read and write in place in buffer
typedef struct {
    sky_entry_t * entry;       // entry without data
    uint8_t * data;            // array size = sizeof(data type) * count
} sky_entry_ext_t;

typedef struct {
    uint8_t sw_version;        // client sw version for request and server sw version for response
    uint8_t timestamp[6];      // timestamp in milliseconds
    uint8_t type;              // payload type
} sky_payload_t;

typedef struct {
    sky_payload_t payload;     // payload without data entries
    sky_entry_ext_t data_entry;// data_entry is updated to iterate over an unbounded array of data entries in buffer
} sky_payload_ext_t;

typedef uint16_t sky_checksum_t;

// enum values to set struct ap_t::flag.
enum SKY_BAND {
    BAND_UNKNOWN = 0,
    BAND_2_4G,
    BAND_5G,
};

//
// protocol payload data entry data types
// location request
// Note: all data types are explicitly padded for 32-bit alignment.
//

/* WARNING:
 * it is important to keep the order
 * the larger size vars first in the structs
 * because the compiler pads the struct to align
 * to the largest size
 */

// access point
// Note: Padding bytes will be appended at the end of the very last "struct ap_t",
//       if the memory boundary of the end is not aligned at 32-bits.
struct ap_t {
    uint8_t MAC[6];
    int8_t rssi;
    uint8_t flag; // bit fields:
                  // bit 0: 1 if the device is currently connected to this AP. 0 otherwise.
                  // bits 1-3: Band indicator. Allowable values:
                  //                                             0: unknown
                  //                                             1: 2.4 GHz
                  //                                             2: 5 GHz
                  //                                             3-7: Reserved
                  // bits 4-7: Reserved
};

// http://wiki.opencellid.org/wiki/API
struct gsm_t {
    uint32_t ci;
    uint32_t age;
    uint16_t mcc; // country
    uint16_t mnc;
    uint16_t lac;
    int8_t rssi; // -255 unkonwn - map it to - 128
    uint8_t unused; // padding byte
};

// 64-bit aligned due to double
struct cdma_t {
    double lat;
    double lon;
    uint32_t age;
    uint16_t sid;
    uint16_t nid;
    uint16_t bsid;
    int8_t rssi;
    uint8_t unused[5]; // padding bytes
};

struct umts_t {
    uint32_t ci;
    uint32_t age;
    uint16_t mcc; // country
    uint16_t mnc;
    uint16_t lac;
    int8_t rssi;
    uint8_t unused; // padding byte
};

struct lte_t {
    uint32_t age;
    uint32_t eucid;
    uint16_t mcc;
    uint16_t mnc;
    int8_t rssi;
    uint8_t unused[3]; // padding bytes
};

union cell_t {
    struct gsm_t gsm;
    struct cdma_t cdma;
    struct umts_t umts;
    struct lte_t lte;
};

// 64-bit aligned due to double
struct gps_t {
    double lat;
    double lon;
    float hdop;
    float alt; // altitude
    float hpe;
    float speed;
    uint32_t age; // last seen in ms
    uint8_t nsat;
    uint8_t fix;
    uint8_t unused[2]; // padding bytes
};

// blue tooth
struct ble_t {
    uint16_t major;
    uint16_t minor;
    uint8_t MAC[6];
    uint8_t uuid[16];
    int8_t rssi;
    uint8_t unused; // padding byte
};

//
// protocol payload data entry data types
// location response
// Note:
// * location_t is the only type 64-bit aligned. All the other types
//   are 32-bit aligned.
// * location_ext_t needs to be reinterpreted in place in buffer,
//   and it is the last data type structure in the response buffer,
//   so it is unnecessary to be padded at the end for 32-bit alignment.
//

// location result
struct location_t {
    double lat; // 64 bit IEEE-754
    double lon; // 64 bit IEEE-754
    float hpe;  // 32 bit IEEE-754
    float distance_to_point; // 32 bit IEEE-754
};

// extended location result
struct location_ext_t {

    uint8_t mac_len;
    uint8_t *mac;

    uint8_t ip_len;
    uint8_t ip_type;  // DATA_TYPE_IPV4 or DATA_TYPE_IPV6
    uint8_t *ip_addr; // ipv4 (4 bytes) or ipv6 (16 bytes)

    uint8_t street_num_len;
    char *street_num;

    uint8_t address_len;
    char *address;

    uint8_t city_len;
    char *city;

    uint8_t state_len;
    char *state;

    uint8_t state_code_len;
    char *state_code;

    uint8_t metro1_len;
    char *metro1;

    uint8_t metro2_len;
    char *metro2;

    uint8_t postal_code_len;
    char *postal_code;

    uint8_t county_len;
    char *county;

    uint8_t country_len;
    char *country;

    uint8_t country_code_len;
    char *country_code;
};

//
// client application data types
//

struct sky_srv_t {
    char url[URL_SIZE]; // URL format - https://en.wikipedia.org/wiki/Uniform_Resource_Locator#Syntax
    char cred[AUTH_SIZE];
};

// relay setting for echoing the location results
struct sky_relay_t {
    struct sky_srv_t srv;
    uint8_t valid;
};

// stores keys in a binary tree
struct sky_key_t {
    uint32_t partner_id;
    uint8_t aes_key[16];  // 128 bit aes key
    char keyid[128];      // api key
    struct sky_relay_t relay; // relay responses
};

struct location_rq_t {

    //
    // protocol attributes
    //

    sky_rq_header_t header;
    sky_payload_ext_t payload_ext;

    uint8_t mac_count; // count of MAC address
    uint8_t *mac;      // client device MAC identifier

    uint8_t ip_count; // count of IP address
    uint8_t ip_type;
    uint8_t *ip_addr; // ipv4 or ipv6

    // wifi access points
    uint8_t ap_count;
    struct ap_t *aps;

    // blue tooth
    uint8_t ble_count;
    struct ble_t *bles;

    // cell
    // note: *DEPRECATED*, please use gsm, cdma, lte, and umts which are defined below.
    uint8_t cell_count; // deprecated, use gsm, cdma, lte and umts instead
    uint8_t cell_type;  // deprecated, use gsm, cdma, lte and umts instead
    union cell_t *cell; // deprecated, use gsm, cdma, lte and umts instead

    // gsm
    uint8_t gsm_count;
    struct gsm_t *gsms;

    // cdma
    uint8_t cdma_count;
    struct cdma_t *cdmas;

    // lte
    uint8_t lte_count;
    struct lte_t *ltes;

    // umts
    uint8_t umts_count;
    struct umts_t *umtss;

    // gps
    uint8_t gps_count;
    struct gps_t *gps;

    //
    // additional attributes
    //

    struct sky_key_t key; // user key
    char *api_version; // api server version number (string 2.34)

    // http server settings
    char *http_url;
    char *http_uri;
};

struct location_rsp_t {

    //
    // protocol_version attributes
    //

    sky_rsp_header_t header;
    sky_payload_ext_t payload_ext;

    //
    // additional attributes
    //

    struct sky_key_t key; // user key

    struct location_t location; // location result: lat and lon

    struct location_ext_t location_ext; // ext location result: full address, etc.
};

// callback function for sending data from buffer
// @param buff - data buffer
// @param buff_len - data length in buffer
// @param host - host name
// @param port - port number
// @param rpc_handle - the remote procedure call handle (e.g. socket) for client-server model communication;
//                    - value is set within sky_tx_fn, and is used by sky_rx_fn.
// @return the number of sent bytes, which should be equivalent to buff_len, upon success,
//         or -1 upon failure.
typedef int32_t (* sky_client_send_fn)(uint8_t *buff, uint32_t buff_len,
        char * host, uint16_t port, void * rpc_handle);

// callback function for receiving data to buffer
// @param buff - data buffer
// @param buff_len - buffer length
// @param rpc_handle - the remote procedure call handle (e.g. socket) for client-server model communication
// @return the number of received bytes upon success, or -1 upon failure.
typedef int32_t (* sky_client_recv_fn)(uint8_t *buff, uint32_t buff_len,
        void * rpc_handle);


/*************************************************************************
 *
 * Skyhook Preliminary APIs for ELGv2 Protocol
 *
 *************************************************************************/

// set the flag of an access point to claim the device is currently connected
void sky_set_ap_connected(struct ap_t* ap, bool is_connected);

// set the flag of an access point for the bandwidth
void sky_set_ap_band(struct ap_t* ap, enum SKY_BAND band);

// initialize the attributes of GPS to default or invalid values
void sky_init_gps_attrib(struct gps_t * gps);

// find aes key  based on partner_id in key root and set it
uint32_t sky_get_partner_id_from_rq_header(uint8_t *buff, uint32_t buff_len);

// called by server
// decode binary data from client, result is in the location_rq_t struct
int32_t sky_decode_req_bin(uint8_t *buff, uint32_t buff_len,
        struct location_rq_t *creq);

// called by server
// encodes the loc struct into binary formatted packet sent to client
// returns the packet len or -1 when fails
int32_t sky_encode_resp_bin(uint8_t *buff, uint32_t buff_len,
        struct location_rsp_t *cresp);

// called by client
// encodes the request struct into binary formatted packet
// returns the packet len or -1 when fails
int32_t sky_encode_req_bin(uint8_t *buff, uint32_t buff_len,
        struct location_rq_t *creq);

// called by client
// decodes the binary data and the result is in the location_rsp_t struct
int32_t sky_decode_resp_bin(uint8_t *buff, uint32_t buff_len,
        struct location_rsp_t *cresp);

/*************************************************************************
 *
 * Skyhook Easy APIs for ELGv2 Protocol client
 *
 *************************************************************************/

// parse url out for host and port
// @param url [in] - in format of "elg://host:port/", array length is URL_SIZE
// @param host [in] - host name in url, array length is HOST_SIZE
// @param port [in] - port number in url, array length is PORT_SIZE
// @return true for success or false for failure
bool sky_parse_url(char * url, char * host, uint16_t * port);

// print binary buffer in HEX to console
// @param buff [in] - binary buffer
// @param len [in] - buffer length
void print_buff(uint8_t *buff, uint32_t len);

// print binary buffer in HEX to array
// @param buff [in] - binary buffer
// @param len [in] - buffer length
// @param hex_buff [out] - HEX buffer
// @param hex_buff_len [in] - HEX buffer length
// @return the data length in HEX buffer for success, or -1 for failure
int32_t sprint_buff(uint8_t *hex_buff, uint32_t hex_buff_len, uint8_t *buff, uint32_t buff_len);

// Called by the client to encode, encrypt and send a location request to Skyhook location service.
// @param rq [in] - client's location request
// @param rpc_send [in] - callback function for sending out data buffer
// @param url [in] - destination server and port in the format of "elg://host:port/"
// @param rpc_handle [out] - the RPC call handle to mask the underlying communication details
// @return the number of sent bytes (in ELG request) upon success, or -1 upon failure.
int32_t sky_send_location_request(struct location_rq_t * rq,
        sky_client_send_fn rpc_send, char * url, void * rpc_handle);

// Called by the client to receive, decrypt and decode Skyhook location service's response.
// @param rsp [out] - server's location response
// @param rpc_recv [in] - callback function for receiving data
// @param rpc_handle [in] - the RPC call handle to mask the underlying communication details
// @return the number of received bytes (in ELG response) upon success, or -1 upon failure.
int32_t sky_recv_location_response(struct location_rsp_t *rsp,
        sky_client_recv_fn rpc_recv, void * rpc_handle);

// Called by the client to query location.
// - Simple blocking call to invoke sky_send_location_request() and sky_recv_location_response() automatically.
// - If nonblocking calls are desirable, invoke sky_send_location_request() and sky_recv_location_response() directly
//   instead of invoking this simple blocking call.
// @param rq [in] - client's location request
// @param rpc_send [in] - callback function for sending out data buffer
// @param url [in] - destination server and port in the format of "elg://host:port/"
// @param rsp [out] - server's location response
// @param rpc_recv [in] - callback function for receiving data
// @param rpc_handle [in] - the RPC call handle for tx and rx
// @return true for success, or false for failure
bool sky_query_location(
        struct location_rq_t * rq, sky_client_send_fn rpc_send, char * url,
        struct location_rsp_t *rsp, sky_client_recv_fn rpc_recv, void * rpc_handle);

#endif

#ifdef __cplusplus
}
#endif
