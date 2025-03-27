#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

struct SAppearance
{
	uint32 signature;
	uint8 offs0004[104];
};


struct SAppearanceFile
{
	uint32 signature;
	uint16 version; // always 1?
	uint16 offs0006;
	uint32 offs0008;
	uint8 offs000c[32];
	uint32 offs002c;
	uint32 offs0030; // 0x60?
	uint32 offs0034;
	uint32 offs0038;
	uint32 offs003c; // 0x88000000?
	uint32 offs0040; // 0x330? seems to not change
	uint32 offs0044;
	uint32 offs0048;
	uint8 offs004c[34];
	uint8 offs007f;
};


class HXAPI UUserInterface
{
public:
	static SAppearance * NewAppearance();
};

#include "_mwexpoff.h"
