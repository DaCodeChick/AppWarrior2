#include "../include/GrafTypes.hpp"
#include "../include/UApplication.hpp"
#include "../include/UMath.hpp"
#include "../include/UMemory.hpp"

#include <cmath>

#ifndef _WIN32 && !defined(_MACINTOSH)
#include <sys/time.h>
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
	uint32 tbl;

	asm
	{
		mftb tbl, TBLr
	}

	return tbl;
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


uint64 UMath::Div64U(uint64 inNumerator, uint64 inDenominator, uint64 *outRemainder)
{
	uint32 hin = (uint32)(inNumerator >> 32);
	uint32 lon = (uint32)inNumerator;
	uint32 hid = (uint32)(inDenominator >> 32);
	uint32 lod = (uint32)inDenominator;
	uint32 hiq = 0, loq = 0, hir = 0, lor = 0;

	// if the denom. is 32-bit (high is zero)
	if (!hid)
	{
		if (hin < lod)
		{
			loq = (uint32)(inNumerator / lod);
			lor = (uint32)(inNumerator % lod);
		}
		else
		{
			if (!lod)
				lod = (uint32)(1 / 0); // undefined behavior
			
			uint64 inter = ((uint64)(hin % lod) << 32) | lon;

			hiq = hin / lod;
			loq = (uint32)(inter / lod);
			lor = (uint32)(inter % lod);
		}

		if (outRemainder)
			*outRemainder = (uint64)lor;
	}
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
