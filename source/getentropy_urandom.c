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
 * Emulates getentropy using /dev/urandom.
 */

#include "xp_getentropy.h"
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#if !defined(XP_RANDOM_FILE)
#define XP_RANDOM_FILE "/dev/urandom"
#endif

int xp_getentropy(void *buf, size_t len) {
    if (len > 256) {
        errno = EIO;
        return -1;
    }
    struct stat st;
    int fd, flags;
    int save_errno = errno;

start:
    flags = O_RDONLY | O_NOFOLLOW | O_CLOEXEC;
    fd = open(XP_RANDOM_FILE, flags, 0);
    if (fd == -1) {
        if (errno == EINTR) goto start;
        goto nodevrandom;
    }

    // Lightly verify that the device node looks sane
    if (fstat(fd, &st) == -1 || !S_ISCHR(st.st_mode)) {
        close(fd);
        goto nodevrandom;
    }

    for (size_t i = 0; i < len;) {
        size_t wanted = len - i;
        ssize_t ret = read(fd, (char *)buf + i, wanted);

        if (ret == -1) {
            if (errno == EAGAIN || errno == EINTR) continue;
            close(fd);
            goto nodevrandom;
        }
        i += (size_t)ret;
    }
    close(fd);
    errno = save_errno;
    return 0;

nodevrandom:
    errno = EIO;
    return -1;
}
