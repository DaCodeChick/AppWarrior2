#pragma once

#include "typedefs.hpp"


class HXAPI UCryptTransact
{
public:
	static uint32 Crypt(uint32 inKey, const void *ioData, Size inSize);
};
