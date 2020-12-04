// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

// clang-format off
#include "getentropy_xp.h"
// sys/random.h is not self-contained on macOS. It needs Availibility.h before it.
#include <Availibility.h>
#include <sys/random.h>
#include <errno.h>
// clang-format on

int getentropy_xp(void *buf, size_t len) {
    if (getentropy(buf, len) == -1) {
        // macOS sets errno to EINVAL for invalid address. Standard OpenBSD behavior is
        // EFAULT.
        if (errno == EINVAL) {
            errno = EFAULT;
        }
        return -1;
    }
    return 0;
}
