// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.
//
// Emulates getentropy under macOS.

// clang-format off
#include "xp_getentropy.h"
// sys/random.h is not self-contained on macOS. It needs Availibility.h before it.
#include <Availability.h>
#include <sys/random.h>
#include <errno.h>
// clang-format on

int xp_getentropy(void* buf, uint32_t len) {
    if (getentropy(buf, len) == -1) {
        // macOS sets errno to EINVAL if len > 256, contrary to the man page.
        // See
        // https://opensource.apple.com/source/xnu/xnu-6153.141.1/bsd/dev/random/randomdev.c.auto.html.
        // Rectify to conform to OpenBSD behavior.
        if (errno == EINVAL) {
            errno = EIO;
        }
        return -1;
    }
    return 0;
}
