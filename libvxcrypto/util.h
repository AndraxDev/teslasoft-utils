#ifndef LIBVXCRYPTO_UTIL_H
#define LIBVXCRYPTO_UTIL_H

unsigned char* sha256(char* text);
int bit_encoder(unsigned char block, unsigned char* key);

#endif //LIBVXCRYPTO_UTIL_H
