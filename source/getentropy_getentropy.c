// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

#include "xp_getentropy.h"
#include <unistd.h>

int xp_getentropy(void* buf, uint32_t len) {
    return getentropy(buf, len);
}
