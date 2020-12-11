# getentropy cross-platform

[![builds.sr.ht status](https://builds.sr.ht/~aman/xp-getentropy.svg)](https://builds.sr.ht/~aman/xp-getentropy?)
[![GitHub Actions status](https://github.com/a-vrma/xp-getentropy/workflows/GitHub%20CI/badge.svg)](https://github.com/a-vrma/xp-getentropy/actions)

A cross-platform way to get cryptographically-secure random bytes.

Tested on:

- Linux 5.4 with glibc (Arch)
- Linux 5.4 with musl (Alpine)
- Linux 4.4 with glibc (Ubuntu 16.04)
- Linux 3.10 with glibc (CentOS 7)
- FreeBSD 11.4 and 12.2
- OpenBSD 6.7
- macOS 10.14, 10.15, and 11
- Emscripten 2.0.10 (not WASM, just the JS output)
- Windows Server 2019 with MSVC 16.8
- Windows Server 2016 with MSVC 15.9

**This library is in a very experimental state. Please wait until I tag a
release to start using it**.

## usage

There is a single function, `xp_getentropy`. It works like this:

```c
/// Fill a buffer with high-quality entropy. The maximum permitted buffer size is
/// 256 bytes.
/// @param[out] buf The buffer to fill.
/// @param[in] len The length of the buffer, in bytes.
/// @return 0 on success and -1 on failure.
int xp_getentropy(void *buf, size_t len);
```

## legal

Parts are copied from LibreSSL Portable under the ISC license. Parts that I
wrote are also distributed under the ISC license. See [LICENSE](LICENSE) file
for details.
