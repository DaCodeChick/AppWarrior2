#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

typedef class TMessageSysObj *TMessageSys;

class HXAPI UMessageSys
{
public:
	static void Deinit();
	static void Init();
	static void Dispose(TMessageSys inSys);

	static bool Execute(TMessageSys inSys);
};


class HXAPI TMessageSysObj
{
public:
	void operator delete(void *p)
	{
		UMessageSys::Dispose((TMessageSys)p);
	}
protected:
	TMessageSysObj()
	{
	}
};

#include "_mwexpoff.h"
