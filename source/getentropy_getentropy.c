// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

#include "getentropy_xp.h"
#include <unistd.h>

int getentropy_xp(void *buf, size_t len) {
    return getentropy(buf, len);
}
