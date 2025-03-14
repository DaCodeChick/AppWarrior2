#pragma once

#include "GrafTypes.hpp"


struct SFontDesc
{
	uint32 signature;
	uint8 offs0004[20];
	uint8 nameLength;
	char name[31];
	uint8 offs0038[34];
	uint8 authorLength;
	char author[31];
};


class HXAPI UGraphics
{
public:
	static uint32 BlendColor(uint32 inColor, int32 inFactor);
	static uint32 ScaleColor(uint32 inColor, int32 inFactor);

	static void ComputeBoundingBox(SRect &inRect, uint32 inRadius, SBoundingBox &outBB);
};
