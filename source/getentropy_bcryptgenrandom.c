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
#include <bcrypt.h>
#include <stdint.h>
#include <windows.h>

#pragma comment(lib, "bcrypt.lib")

/*
 * On Windows, BCryptGenRandom with BCRYPT_USE_SYSTEM_PREFERRED_RNG is supposed
 * to be a well-seeded, cryptographically strong random number generator.
 * https://docs.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgenrandom
 */
int xp_getentropy(void *buf, size_t len) {
    if (len > 256) {
        return -1;
    }

    if (FAILED(BCryptGenRandom(NULL, buf, len, BCRYPT_USE_SYSTEM_PREFERRED_RNG))) {
        return -1;
    }

    return 0;
}
