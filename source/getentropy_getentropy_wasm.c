// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.
//
// Emulates getentropy under WASI.

#include "xp_getentropy.h"
#include <sys/random.h>
#include <errno.h>

int xp_getentropy(void* buf, uint32_t len) {
    if (getentropy(buf, len) != 0) {
        // WASI sets ENOTTY when len is greater than 256 for some reason.
        if (errno == ENOTTY) {
            errno = EIO;
        }
        return -1;
    }
    return 0;
}
