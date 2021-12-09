#include "xp_getentropy.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>

#define SIZE 256

int main(void) {
    uint8_t bs[SIZE];

    int res = xp_getentropy(bs, SIZE);
    if (res == -1) {
        fputs("Getting entropy failed.\n", stdout);
        fprintf(stdout, "Errno was %d.\n", errno);
        fprintf(stdout, "EIO is %d.\n", EIO);
        return 1;
    }

    for (size_t i = 0; i < SIZE; ++i) {
        printf("%02x", bs[i]);
        if ((i + 1) % 8 == 0) putchar('\n');
    }

    fputs("Getting entropy succeeded.\n", stdout);
    return 0;
}
