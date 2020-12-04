#include "xp_getentropy.h"
#include <stdio.h>
#include <stdint.h>
#define SIZE 256

int main(void) {
    uint8_t bs[SIZE];

    int res = xp_getentropy(bs, SIZE);
    if (res == -1) {
        fputs("Getting entropy failed.\n", stdout);
        return 1;
    }

    for (size_t i = 0; i < SIZE; ++i) {
        printf("%02x", bs[i]);
        if ((i + 1) % 8 == 0) putchar('\n');
    }

    fputs("Getting entropy succeeded.\n", stdout);
    return 0;
}
