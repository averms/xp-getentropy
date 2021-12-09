// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.
//
// Emulates getentropy under WASM.

#include "xp_getentropy.h"
#include <sys/random.h>
#include <errno.h>

int xp_getentropy(void* buf, uint32_t len) {
    // WASI does not have the 256 byte limitation. At least according to preliminary
    // tests with emscripten.
    // if (len > 256) {
    //     errno = EIO;
    //     return -1;
    // }
    return getentropy(buf, len);
}
