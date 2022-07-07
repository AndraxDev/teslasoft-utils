#include "decrypt.h"
#include "base64.h"
#include "encrypt.h"

#include <string.h>

char* decrypt(char* text, char* key) {
    char* raw = (char*) b64_decode(text, strlen(text));
    char* encoded = encrypt(raw, key);
    char* out = (char*) b64_decode(encoded, strlen(encoded));
    return out;
}