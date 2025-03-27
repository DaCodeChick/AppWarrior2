#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"


class HXAPI UBitString
{
public:
	static void Set(void *ioData, uint32 inIndex, uint32 inCount, bool inValue);
};

#include "_mwexpoff.h"
