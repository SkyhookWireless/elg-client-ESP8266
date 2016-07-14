#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "hmac256.h"

#define KEY_SIZE 64
#define MESSAGE_SIZE 64

void sha(unsigned char *clrtext, unsigned char *ciph);
void hmac(char *k, int k_len, char *m, unsigned char *ciph);
void pad_array_with(char pad, char *array, size_t sz);
bool check(char *k, int k_len, char *m, unsigned char *mac);
