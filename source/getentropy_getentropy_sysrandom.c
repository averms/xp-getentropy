// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

// sys/random.h is not self-contained on macOS. It needs sys/stat.h, which includes
// Availibility.h, before it.
// clang-format off
#include "getentropy_xp.h"
#include <sys/stat.h>
#include <sys/random.h>
// clang-format on

int getentropy_xp(void *buf, size_t len) {
    return getentropy(buf, len);
}
