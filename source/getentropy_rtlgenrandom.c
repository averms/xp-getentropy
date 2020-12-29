// © 2020 Aman Verma <https://aman.raoverma.com/contact.html>
// Distributed under the ISC license, see LICENSE file for details.

#include "xp_getentropy.h"
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <windows.h>

// On Windows, RtlGenRandom[1] is supposed to output cryptographically-secure random
// bytes[2]. Despite the warning in the docs, it will probably not be removed[3].
//
// [1]: https://docs.microsoft.com/en-us/windows/win32/api/ntsecapi/nf-ntsecapi-rtlgenrandom
// [2]: https://www.microsoft.com/security/blog/2019/11/25/going-in-depth-on-the-windows-10-random-number-generation-infrastructure/
// [3]: https://github.com/rust-random/rand/issues/111#issuecomment-316140155.

#define RtlGenRandom SystemFunction036
BOOLEAN NTAPI RtlGenRandom(PVOID RandomBuffer, ULONG RandomBufferLength);

int xp_getentropy(void* buf, size_t len) {
    if (len > 256) {
        errno = EIO;
        return -1;
    }

    if (!RtlGenRandom((PVOID)buf, (ULONG)len)) {
        errno = EIO;
        return -1;
    }

    return 0;
}
