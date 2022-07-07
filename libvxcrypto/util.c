#include <openssl/sha.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

unsigned char* sha256(char* text) {
    unsigned char ar[strlen(text)];
    for (int i = 0; i < strlen(text); ++i) {
        ar[i] = (unsigned char) text[i];
    }

    unsigned char *d = SHA256(ar, strlen(text), 0);

    unsigned char* hash = calloc(SHA256_DIGEST_LENGTH, sizeof (char*));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hash[i] = d[i];
    }
    return hash;
}

int bit_encoder(unsigned char block, unsigned char* key) {
    int key_length = (int) strlen((char*) key);

    if (key_length != 8) return '\n';

    int block_bit[8];
    int block_key[64];

    int block_to_int = (int) block;

    for (int i = 0; i < 8; ++i) {
        block_bit[7 - i] = abs(block_to_int % 2);
        block_to_int /= 2;
    }

    for (int i = 0; i < 8; ++i) {
        int key_bl = (int) key[i];
        for (int j = 0; j < 8; ++j) {
            block_key[7 - j + (i * 8)] = key_bl % 2;
            key_bl /= 2;
        }
    }
    int xor_1[32];
    int x = 0;
    for (int i = 0; i < 8; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if (block_key[i*8 + j] == 1 && block_key[i*8 + j + 8] == 1) {
                xor_1[x + j] = 1;
            } else if (block_key[i*8 + j] == 0 && block_key[i*8 + j + 8] == 0) {
                xor_1[x + j] = 1;
            } else {
                xor_1[x + j] = 0;
            }
        }
        x+=8;
    }

    int xor_2[32];
    int y = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; ++j) {
            if (xor_1[i*8 + j] == 1 && xor_1[i*8 + j + 4] == 1) {
                xor_2[y+j] = 1;
            } else if (xor_1[i*8 + j] == 0 && xor_1[i*8 + j + 4] == 0) {
                xor_2[y+j] = 1;
            } else {
                xor_2[y+j] = 0;
            }
        }

        for (int j = 0; j < 4; ++j) {
            xor_2[y+j + 4] = xor_2[y+j];
        }

        y+=8;
    }

    int xor_3[16];
    int z = 0;
    for (int i = 0; i < 4; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if (xor_2[i*8 + j] == 1 && xor_2[i*8 + j + 8] == 1) {
                xor_3[z+j] = 1;
            } else if (xor_2[i*8 + j] == 0 && xor_2[i*8 + j + 8] == 0) {
                xor_3[z+j] = 1;
            } else {
                xor_3[z+j] = 0;
            }
        }
        z+=8;
    }

    int xor_4[8];
    int a = 0;
    for (int i = 0; i < 2; i+=2) {
        for (int j = 0; j < 8; ++j) {
            if (xor_3[i*8 + j] == 1 && xor_3[i*8 + j + 8] == 1) {
                xor_4[a+j] = 1;
            } else if (xor_3[i*8 + j] == 0 && xor_3[i*8 + j + 8] == 0) {
                xor_4[a+j] = 1;
            } else {
                xor_4[a+j] = 0;
            }
        }
        a+=8;
    }

    int xor_5[8];
    for (int j = 0; j < 8; ++j) {
        if (block_bit[j] == 1 && xor_4[j] == 1) {
            xor_5[j] = 1;
        } else if (block_bit[j] == 0 && xor_4[j] == 0) {
            xor_5[j] = 1;
        } else {
            xor_5[j] = 0;
        }
    }

    int d = 128;
    int out = 0;
    for (int i = 0; i < 8; ++i) {
        if (xor_5[i] == 1) out += d;
        d /= 2;
    }

    return out;
}