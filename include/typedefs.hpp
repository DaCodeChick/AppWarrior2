#pragma once

#ifdef _WIN32

#define HXAPI __declspec(dllexport)

#include <windows.h>

#ifdef _WIN64
#define BITS_64

typedef LONG int64;
typedef ULONG uint64;
#else // _WIN64
#define BITS_32

typedef LONGLONG int64;
typedef ULONGLONG uint64;
#endif // _WIN64

typedef CHAR int8;
typedef SHORT int16;
typedef INT int32;
typedef BYTE uint8;
typedef WORD uint16;
typedef DWORD uint32;
typedef SIZE_T Size;
typedef UINT_PTR uintptr;
typedef HANDLE Handle;

typedef CHAR char8;
typedef WCHAR char16;

#elif defined(macintosh) || (defined(__APPLE__) && defined(__powerpc__)) // _WIN32

#define _MACINTOSH

#include <MacTypes.h>

typedef SInt64 int64;
typedef UInt64 uint64;

typedef SInt8 int8;
typedef SInt16 int16;
typedef SInt32 int32;
typedef UInt8 uint8;
typedef UInt16 uint16;
typedef UInt32 uint32;
typedef Size uintptr;

typedef char char8;
typedef UniChar char16;

#ifdef __ppc64__
#define BITS_64
#else // __ppc64__
#define BITS_32
#endif // __ppc64__

#else // _WIN32

#ifdef _LP64
#define BITS_64
#include <stdint.h>

typedef long int64;
typedef unsigned long uint64;
#else // _LP64
#define BITS_32

typedef long long int64;
typedef unsigned long long uint64;
#endif // _LP64

typedef char int8;
typedef short int16;
typedef int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef size_t Size;
typedef uintptr_t uintptr;

typedef char char8;
typedef wchar_t char16;
#endif // _WIN32

typedef double fast_float;


#ifdef BITS_64
#define PTR_ALIGN 8
#define PTR_ALIGN_MASK 7
#else
#define PTR_ALIGN 4
#define PTR_ALIGN_MASK 3
#endif // BITS_64


#define FORCE_CAST(t, d) (*(t *)&(d)) 
#define ADDR_CAST(p) ((uintptr)p)
#define BPTR(p) ((uint8 *)p)
#define CBPTR(p) ((const uint8 *)p)
#define WPTR(p) ((uint16 *)p)
#define CWPTR(p) ((const uint16 *)p)
#define IPTR(p) ((uint32 *)p)
#define CIPTR(p) ((const uint32 *)p)

#ifndef max
template <class T> inline T max(T a, T b)
{
	return (a < b) ? b : a;
}
#endif // max


#ifndef min
template <class T> inline T min(T a, T b)
{
	return (b < a) ? b : a;
}
#endif // min


inline uint16 swap_int(uint16 n)
{
	return (n >> 8) | (n << 8);
}


inline uint32 swap_int(uint32 n)
{
	return (n >> 24) | ((n << 8) & 0xFF0000) |
		((n >> 8) & 0xFF00) | (n << 24);
}
