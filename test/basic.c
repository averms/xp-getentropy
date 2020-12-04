#include "getentropy_xp.h"
#include <stdio.h>
#include <stdint.h>
#define SIZE 256

int main(void) {
    uint8_t bs[SIZE];

    int res = getentropy_xp(bs, SIZE);
    if (res == -1) {
        fputs("Getting entropy failed.\n", stderr);
        return 1;
    }

    for (size_t i = 0; i < SIZE; ++i) {
        printf("%02x", bs[i]);
        if ((i + 1) % 8 == 0) putchar('\n');
    }

    fputs("Getting entropy succeeded.\n", stdout);
    return 0;
}
