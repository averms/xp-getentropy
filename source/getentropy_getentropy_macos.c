// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

// clang-format off
#include "xp_getentropy.h"
// sys/random.h needs Availibility.h and stddef.h before it.
#include <Availability.h>
#include <stddef.h>
#include <sys/random.h>
#include <errno.h>
// clang-format on

int xp_getentropy(void *buf, uint32_t len) {
    if (getentropy(buf, len) != 0) {
        // macOS sets errno to EINVAL if len > 256, contrary to the man page. See
        // https://github.com/apple-oss-distributions/xnu/blob/776661b72c2db9861865df68d309f6f35faccff4/bsd/dev/random/randomdev.c#L235
        // Rectify to conform to OpenBSD behavior.
        if (errno == EINVAL) {
            errno = EIO;
        }
        return -1;
    }
    return 0;
}
