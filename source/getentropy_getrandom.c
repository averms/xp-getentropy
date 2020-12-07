/*
 * Copyright (c) 2014 Theo de Raadt <deraadt@openbsd.org>
 * Copyright (c) 2014 Bob Beck <beck@obtuse.com>
 * Copyright (c) 2020 Aman Verma <https://aman.raoverma.com/contact.html>
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
 * Emulates getentropy using getrandom on Linux, DragonflyBSD, NetBSD, Illumos,
 * and Oracle Solaris.
 */

#include "xp_getentropy.h"
#include <sys/random.h>
#include <errno.h>

int xp_getentropy(void *buf, size_t len) {
    if (len > 256) {
        return -1;
    }

    int pre_errno = errno;
    ssize_t ret;
    // Repeat if interrupted by signal
    do {
        ret = getrandom(buf, len, GRND_NONBLOCK);
    } while (ret < 0 && errno == EINTR);
    if ((size_t)ret != len) {
        return -1;
    }
    errno = pre_errno;
    return 0;
}
