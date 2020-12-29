# getentropy cross-platform

[![builds.sr.ht status](https://builds.sr.ht/~aman/xp-getentropy.svg)](https://builds.sr.ht/~aman/xp-getentropy?)
[![GitHub Actions status](https://github.com/a-vrma/xp-getentropy/workflows/GitHub%20CI/badge.svg)](https://github.com/a-vrma/xp-getentropy/actions)
[![Appveyor status](https://ci.appveyor.com/api/projects/status/75kw22knil3leahx?svg=true)](https://ci.appveyor.com/project/ayofloweshiou/xp-getentropy)

A cross-platform way to get cryptographically-secure random bytes.

**This library is in a very experimental state. Please wait until I tag a
release to consider depending on it**.

## usage

There is a single function, `xp_getentropy`. It is documented in the header
file [`xp_gentropy.h`](include/xp_getentropy.h).

## platforms

Should work on any platform with a C99 compiler.
Tested on:

- Various Linux distros from kernel 3.10 up to 5.4
- FreeBSD 11.4 and 12.2
- OpenBSD 6.7
- NetBSD 9.1
- DragonflyBSD 5.8.3
- macOS 10.14, 10.15, and 11
- OpenIndiana Hipster 2020.10
- Windows Server 2019 with MSVC 16.8
- Windows Server 2016 with MSVC 15.9
- Cygwin 3.0.7
- Emscripten 2.0.10 (not WASM, just the JS output)

## legal

Parts are copied from LibreSSL Portable under the ISC license. Parts that I
wrote are also distributed under the ISC license. See [LICENSE](LICENSE) file
for details.
