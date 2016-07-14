/************************************************
 * Authors: Istvan Sleder and Marwan Kallal
 * 
 * Company: Skyhook Wireless
 *
 ************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SKY_CRYPT_H
#define SKY_CRYPT_H

#include "sky_types.h"

/* generate initialization vector */
void sky_gen_iv(unsigned char *iv);

/* encrypt data */
int sky_aes_encrypt(unsigned char *data, uint32_t data_len, unsigned char *key,
        unsigned char *iv);

/* decrypt data */
int sky_aes_decrypt(unsigned char *data, uint32_t data_len, unsigned char *key,
        unsigned char *iv);

uint16_t fletcher16(uint8_t const *buff, int buff_len);

#endif

#ifdef __cplusplus
}
#endif
