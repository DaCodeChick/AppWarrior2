#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"


class HXAPI UCryptTransact
{
public:
	static uint32 Crypt(uint32 inKey, const void *ioData, Size inSize);
};

#include "_mwexpoff.h"
