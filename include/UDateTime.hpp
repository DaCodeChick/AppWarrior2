#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

enum
{
	kYear_Months = 12,
	kYear_Days = 365,
	kYear_Seconds = 31536000,

	kLeapYear_Days = 366,
	kLeapYear_Seconds = 31622400,

	kDay_Hours = 24,
	kDay_Seconds = 86400,

	kHour_Minutes = 60,
	kHour_Seconds = 3600
};


struct SCalendarDate
{
	int16 _0;
	int16 utcOffset;
	int16 year;
	int16 month;
	int16 day;
	int16 hour;
	int16 minute;
	int16 second;
	int16 weekDay;
};


class HXAPI UDateTime
{
public:
	static uint32 GetMilliseconds();
	static uint64 GetMilliseconds64();
	static int32 GetTimeZoneDelta();
};

#include "_mwexpoff.h"
