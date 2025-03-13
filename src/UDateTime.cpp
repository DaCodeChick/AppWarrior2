#include "../include/UDateTime.hpp"

#ifdef _MACINTOSH
#include <DateTimeUtils.h>
#include <UTCUtils.h>
#endif

#ifdef _WIN32
#define _EPOCH 0x894DEB84400LL
#endif


uint32 UDateTime::GetMilliseconds()
{
#ifdef _WIN32
	return GetTickCount();
#elif defined(_MACINTOSH)
#else
#endif
}


uint64 UDateTime::GetMilliseconds64()
{
#ifdef _WIN32
	FILETIME ft;

	GetSystemTimeAsFileTime(&ft);

	return m64 - _EPOCH;
#elif defined(_MACINTOSH)
#else
#endif
}


int32 UDateTime::GetTimeZoneDelta()
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;

	if (GetTimeZoneInformation(&tzInfo) == TIME_ZONE_ID_DAYLIGHT)
		tzInfo.Bias += tzInfo.DaylightBias;

	return tzInfo.Bias * -kHour_Minutes;	
#elif defined(_MACINTOSH)
	uint32 dt = 0, diff = 0;

	GetDateTime(&dt);
	ConvertDateTimeToUTC(dt, &diff);
	return dt - diff;
#else
#endif
}
