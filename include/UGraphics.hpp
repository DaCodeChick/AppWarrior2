#pragma once

#include "GrafTypes.hpp"


struct SFont
{
	uint32 signature;
};


class HXAPI UGraphics
{
public:
	static uint32 BlendColor(uint32 inColor, int32 inFactor);
	static uint32 ScaleColor(uint32 inColor, int32 inFactor);

	static void ComputeBoundingBox(SRect &inRect, uint32 inRadius, SBoundingBox &outBB);
};
