/*
 * Copyright (c) 2014 Theo de Raadt <deraadt@openbsd.org>
 * Copyright (c) 2014 Bob Beck <beck@obtuse.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Emulates getentropy using BCryptGenRandom.
 */

#include "xp_getentropy.h"
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>
#include <windows.h>

/*
 * On Windows, RtlGenRandom is supposed to output cryptographically-secure random bytes.
 * Despite the warning in the docs, it will probably not be removed:
 * https://github.com/rust-random/rand/issues/111#issuecomment-316140155.
 *
 * https://docs.microsoft.com/en-us/windows/win32/api/ntsecapi/nf-ntsecapi-rtlgenrandom
 * https://www.microsoft.com/security/blog/2019/11/25/going-in-depth-on-the-windows-10-random-number-generation-infrastructure/
 */
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
