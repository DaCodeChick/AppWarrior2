#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

typedef class TTimerObj *TTimer;


class HXAPI UTimer
{
public:
	static TTimer StartNew();
	static void Dispose(TTimer inRef);
};


class TTimerObj
{
public:
	void operator delete(void *p)
	{
		UTimer::Dispose((TTimer)p);
	}
};

#include "_mwexpoff.h"
