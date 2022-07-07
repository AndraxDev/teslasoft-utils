#include "encrypt.h"
#include "util.h"
#include "base64.h"

#include <stdlib.h>
#include <string.h>

char* encrypt(char* text, char* key) {
    unsigned char* key_l = sha256(key);
    unsigned long int text_len = strlen(text);
    unsigned long int blocks_size = text_len;
    unsigned long int blocks_count = 0;
    unsigned long int parts_count = 0;

    while (blocks_size % 32 != 0) blocks_size++;

    char block_text[blocks_size];

    for (unsigned long int i = 0; i < text_len; ++i) {
        block_text[i] = text[i];
    }

    for (unsigned long int i = text_len; i < blocks_size; ++i) {
        block_text[i] = 0;
    }

    for (unsigned long int i = 0; i < blocks_size; ++i) {
        if (i % 4 == 0) {
            blocks_count++;
        }

        if (i % 32 == 0) parts_count++;
    }

    unsigned char cipher[blocks_size];

    for (int i = 0; i < blocks_count; ++i) {
        for (int j = 0; j < 4; ++j) {
            unsigned char* sub_key = calloc(8, sizeof (char*));
            for (int k = 0; k < 8; ++k) {
                sub_key[k] = key_l[j*8 + k];
            }

            cipher[i * 4 + j] = bit_encoder(block_text[i * 4 + j], sub_key);
        }
    }

    unsigned char* cipher_data = calloc(blocks_size, sizeof (char*));
    for (int i = 0; i < blocks_size; ++i) {
        cipher_data[i] = cipher[i];
    }

    char* output = b64_encode(cipher_data, blocks_size);

    free(cipher_data);
    return output;
}