Brief
=====

All Haxial's products seem to have used an altered variation of Hotline Communications Ltd.'s AppWarrior with additional and changed functionality. As such, I am calling this reverse engineer AppWarrior 2. It aims to provide as close a reimplementation to Haxial's proprietary library as possible, with some optimal differences. For vintage Mac enthusiasts, AppWarrior 2 supports Mac OS Carbon via Metrowerks CodeWarrior, or else CMake is used to build. The source is written in a messy combo of C++03 and C for API compatibility. AppWarrior 2 is meant for compatibility and research and is NOT suitable for modern real world use.

Changes and Additions versus AppWarrior 1
=========================================

- More ANSI Pascal string routines added
- Unicode support
- UMemory adds Fill8/16/32 memory fill routines. `UMemory::Fill` simply inlines to `UMemory::Fill8`.
- `UMemory::Checksum()` is now based on the FNV-1a hashing algorithm
- Haxial-centric font, appearance and sound file support
- Structured data now has integrity checks
- Revamped error system
- Unix support added
- UTransport/URegularTransport has been renamed to UNetwork for simplicity
