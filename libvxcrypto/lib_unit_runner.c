#include <stdio.h>
#include <string.h>

#include "encrypt.h"
#include "decrypt.h"
#include "base64.h"

int main() {
    char* text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed aliquet libero vitae placerat iaculis. Morbi tincidunt turpis nec eros viverra, in laoreet nulla egestas. Quisque eget leo ac dolor consequat scelerisque. Ut nibh nulla, pulvinar sit amet ipsum sit amet, varius aliquam arcu. Vestibulum placerat nulla sed sodales faucibus. Sed molestie nisi lacus, sed ultrices ex placerat at. Sed vel dictum neque. Pellentesque risus massa, pulvinar at facilisis non, imperdiet quis ante. Nunc porttitor porta nunc, ut tincidunt mi porta eget. Vivamus eu metus odio. Ut euismod vitae quam commodo molestie. Quisque posuere eget tellus non fringilla. Duis interdum risus metus, at tincidunt arcu finibus imperdiet. Proin sed augue nibh. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur condimentum porta lorem, ac pretium nisl facilisis non. Praesent quis hendrerit lacus. Praesent euismod gravida bibendum. In luctus condimentum tincidunt. Pellentesque quis cursus eros, vel volutpat nisi. Ut sapien dolor, posuere ac faucibus a, dapibus vel felis. Cras tristique diam purus, vitae lacinia purus mattis sed. Suspendisse congue laoreet fringilla. Maecenas leo turpis, tempor vitae magna eget, lobortis interdum nulla. Vivamus condimentum arcu hendrerit felis rutrum aliquam. Morbi ornare fringilla eros sed cursus. Fusce sit amet quam quis metus egestas eleifend egestas ut purus. Cras enim nisi, blandit sed velit non, euismod facilisis ligula.";
    char* key = "password";
//    char* incorrect_key = "passw0rd";
    printf("Text:\n%s\n", text);
    printf("Key:\n%s\n", key);
    char* enc = encrypt(text, key);
    printf("Encrypted text:\n%s\n", enc);
    // printf("Raw cipher:\n%s\n", b64_decode(enc, strlen(enc)));

    char* text2 = "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";
    char* dec = decrypt(text2, key);
    printf("Decrypted text:\n%s\n", dec);

    int validator = 0;
    if (strcmp(text, dec) == 0) validator = 1;
    printf("Validator: %d\n", validator);
//    unsigned char* k = (unsigned char*) "ABCDEFGH";
//    unsigned char s = (char) bit_encoder('A', k);
//    unsigned char d = (char) bit_decoder(s, k);
//    printf("A, %d, %d\n", s, d);
    return 0;
}