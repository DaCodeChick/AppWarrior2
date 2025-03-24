#include "../include/GrafTypes.hpp"
#include "../include/UApplication.hpp"
#include "../include/UMath.hpp"
#include "../include/UMemory.hpp"

#include <math.h>

#ifndef _WIN32 && !defined(_MACINTOSH)
#include <sys/time.h>
#else
#endif // _WIN32

static uint8 _gIndex;
static uint32 _gRandomSeed = 0;


fast_float UMath::ArcTangent(fast_float x)
{
	return atan(x);
}


uint32 UMath::CalcRandomSeed()
{
#ifdef _WIN32
	FILETIME ft;
	
	GetSystemTimeAsFileTime(&ft);
	return ft.dwLowDateTime;
#elif defined(_MACINTOSH)
#else // _WIN32
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	return tv.tv_usec;
#endif // _WIN32
}


fast_float UMath::Cosine(fast_float x)
{
	return cos(UMath::NormalizeAngle(cos(x)));
}


uint32 UMath::GetRandom()
{
	uint8 *buf = UApplication::GetStateBuffer();
	uint32 hash = UMemory::Checksum(buf, 256, CalcRandomSeed());
	
	if (!_gRandomSeed) _gRandomSeed = hash;
	_gRandomSeed = _gRandomSeed * 0x41C64E6D + 12345;
	hash ^= _gRandomSeed;
	buf[_gIndex] ^= hash;
	_gIndex = hash & 63;

	return hash;
}


fast_float UMath::NormalizeAngle(fast_float x)
{
	return (x / gm_2Pi) * gm_2Pi;
}


fast_float UMath::Sine(fast_float x)
{
	return sin(UMath::NormalizeAngle(sin(x)));
}


fast_float UMath::SquareRoot(fast_float x)
{
	return sqrt(x);
}
