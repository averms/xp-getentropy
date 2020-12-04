#include "getentropy_xp.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#define SIZE 257

int main(void) {
    uint8_t bs[SIZE];

    int res = getentropy_xp(bs, SIZE);
    if (res != -1) {
        for (size_t i = 0; i < SIZE; ++i) {
            printf("%02x", bs[i]);
            if ((i + 1) % 8 == 0) putchar('\n');
        }
        fputs(
            "Getting 257 bytes of entropy somehow succeeded, "
            "which is not what we wanted.\n",
            stdout);
        return 1;
    }

    if (errno == EIO) {
        fputs("Getting entropy failed and errno = EIO, which is what we wanted.\n",
              stderr);
        return 0;
    }
    fputs("Getting entropy failed and errno != EIO, which is not what we wanted.\n",
          stderr);
    return 1;
}
