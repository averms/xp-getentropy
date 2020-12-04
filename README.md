# getentropy cross-platform

A cross-platform way to get cryptographically-secure random bytes.

Tested on:

- Linux 5.4 LTS with glibc (Arch)
- Linux 5.4 LTS with musl (Alpine)
- Linux 5.4 LTS with old glibc (CentOS 7)
- FreeBSD 12.2
- macOS 10.14

## TODO

- always return a valid errno, either EIO or EFAULT.
- test more.
- document.
