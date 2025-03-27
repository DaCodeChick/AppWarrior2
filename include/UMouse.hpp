#pragma once

#include "GrafTypes.hpp"
#include "_mwexpon.h"

class HXAPI UMouse
{
public:
	static int32 GetImage();
	static void SetImage(int32 inID);

	static uint32 GetDoubleClickTime();
	static void GetLocation(SPoint &outLoc);
};

#include "_mwexpoff.h"
