// © 2020 Aman Verma
// Distributed under the ISC license, see LICENSE.txt for details.

#ifndef GETENTROPY_XP_H_30185295
#define GETENTROPY_XP_H_30185295

#include <stddef.h>

/// Fill a buffer with high-quality entropy. The maximum permitted buffer size is 256
/// bytes.
/// @param[out] buf The buffer to fill.
/// @param[in] len The length of the buffer, in bytes.
/// @retval 0 Succeeded.
/// @retval -1 Failed.
int getentropy_xp(void *buf, size_t len);

#endif
