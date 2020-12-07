// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.
//
// Emulates getentropy under macOS.

// clang-format off
#include "xp_getentropy.h"
// sys/random.h is not self-contained on macOS. It needs Availibility.h before it.
#include <Availability.h>
#include <sys/random.h>
// clang-format on

int xp_getentropy(void *buf, size_t len) {
    return getentropy(buf, len);
}
