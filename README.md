# getentropy cross-platform

[![builds.sr.ht status](https://builds.sr.ht/~aman/xp-getentropy.svg)](https://builds.sr.ht/~aman/xp-getentropy?)
[![GitHub Actions status](https://github.com/a-vrma/xp-getentropy/workflows/GitHub%20CI/badge.svg)](https://github.com/a-vrma/xp-getentropy/actions)

A cross-platform way to get cryptographically-secure random bytes.

Tested on:

- Linux 5.4 with glibc (Arch)
- Linux 5.4 with old glibc (CentOS 7)
- Linux 5.4 with musl (Alpine)
- Linux 4.4 with glibc (Ubuntu 16.04)
- Various other Linux distros but nothing super old yet
- FreeBSD 11.4 and 12.2
- OpenBSD 6.7
- macOS 10.14, 10.15, and 11
- Emscripten 2.0.10 (not WASM, just the JS output)

**This library is in a very experimental state. Please wait until I tag a
release to start using it**.
