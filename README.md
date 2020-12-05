# getentropy cross-platform

[![builds.sr.ht status](https://builds.sr.ht/~aman/xp-getentropy.svg)](https://builds.sr.ht/~aman/xp-getentropy?)
[![GitHub Actions status](https://github.com/a-vrma/xp-getentropy/workflows/GitHub%20CI/badge.svg)](https://github.com/a-vrma/xp-getentropy/actions)

A cross-platform way to get cryptographically-secure random bytes.

Tested on:

- Linux 5.4 LTS with glibc (Arch)
- Linux 5.4 LTS with musl (Alpine)
- Linux 5.4 LTS with old glibc (CentOS 7)
- FreeBSD 12.2
- macOS 10.14, 10.15
- Emscripten 2.0.10 (not WASM, just the JS output).

**This library is in a very experimental state. Please wait until I tag a
release to start using it**.
