Brief
=====

All Haxial's products seem to have used an altered variation of Hotline Communications Ltd.'s AppWarrior with additional and changed functionality. As such, I am calling this reverse engineer AppWarrior 2. It aims to provide as close a reimplementation to Haxial's proprietary library as possible, with some optimal differences. For vintage Mac enthusiasts, AppWarrior 2 supports Mac OS Carbon via Metrowerks CodeWarrior, or else CMake is used to build. The source is written in a messy combo of C++03 and C for API compatibility. AppWarrior 2 is meant for compatibility and research and is NOT suitable for modern real world use.

Changes and Additions versus AppWarrior 1
=========================================

- More ANSI Pascal string routines added
- Unicode support
- UMemory adds FillByte/Word/Long memory fill routines. `UMemory::Fill` simply inlines to `UMemory::FillByte`.
- `UMemory::Checksum()` is now based on the FNV-1a hashing algorithm
- Haxial-centric font, appearance and sound file support
- Structured data now has integrity checks
- Revamped error system
- Unix support added
- New QoL macros for 64-bit compatibility
- A new `_MACINTOSH` predefined symbol for working with Mac OS Carbon PPC on Metrowerks CodeWarrior.
- CPtrList and CVoidPtrList are recoded as an intrusive linked list. This is mainly for compatibility with Mac OS Carbon. Modern `std::vector` should be preferred otherwise.
- Lowercase most primitive types
- UCryptTransact implemented


Plans for potential AppWarrior 3.0
==================================
- Update codebase to modern C++ and use the STL
- Rust rewrite?
- Cocoa support?
- More widget types?
- Remove old Mac PPC code
- Change all static classes to namespaces
- Remove CVoidPtrList and CPtrList in favor of `std::vector`
- Removal of most primitive typedefs in favor of `<cstdint>`
- Removal of `max`/`min` in factor of `std::max` and `std::min`
- Strip the memory module of convenience function wrappers (ie. Move/Fill)
- Remove the math module in favor of the STL.
- Remove `swap_int` in favor of `std::byteswap`
- Remove mathematical constants such as `gm_Pi` in favor of `std::numbers`
- Replace variable argument functions with variadic template functions
- Remove the bit string module in favor of either `std::bitset` or `std::vector<bool>`
- Deprecate MD5 hashing functionality
- Remove date time module in favor of `std::chrono`
- Remove file system module in favor of streams and `std::filesystem`
- Pending removal of network module, if upcoming C++ library standard incorporates network functionality
- Removal or stripping down the text module in favor of STL string and encoding functionality
- Is the error module even needed today?
