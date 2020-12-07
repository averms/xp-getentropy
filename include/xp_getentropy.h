// © 2020 Aman Verma
// Distributed under the ISC license, see LICENSE.txt for details.

#ifndef XP_GETENTROPY_H_30185295
#define XP_GETENTROPY_H_30185295

#include <stddef.h>

/// Fill a buffer with high-quality entropy. The maximum permitted buffer size is
/// 256 bytes.
/// @param[out] buf The buffer to fill.
/// @param[in] len The length of the buffer, in bytes.
/// @return 0 on success and -1 on failure.
int xp_getentropy(void *buf, size_t len);

#endif
