#pragma once

#include "typedefs.hpp"

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
