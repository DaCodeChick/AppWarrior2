#include "../include/UGraphics.hpp"
#include "../include/UMath.hpp"
#include "../include/UMemory.hpp"


uint32 UGraphics::BlendColor(uint32 inColor, int32 inFactor)
{
	uint32 r = inColor >> 8 & 255;
	uint32 g = inColor >> 16 & 255;
	uint32 b = inColor >> 24;

	if (r) r = 255 - ((255 - r) * inFactor) / 255;
	if (g) g = 255 - ((255 - g) * inFactor) / 255;
	if (b) b = 255 - ((255 - b) * inFactor) / 255;

	return (g & 255) << 16 | (r & 255) << 8 | b << 24;
}


void UGraphics::ComputeBoundingBox(SRect &inRect, uint32 inRadius, SBoundingBox &outBB)
{
	if (inRadius < 2)
	{
		UMemory::Clear(&outBB, sizeof(SBoundingBox));
		return;
	}

	uint32 halfRadius = inRadius >> 1;
	uint32 adjustedRadius = inRadius & 1 ? halfRadius + 1 : halfRadius;
	int32 dx = inRect.right - inRect.left;
	int32 dy = inRect.bottom - inRect.top;

	if (!dx && !dy)
	{
		outBB = {
			{
				inRect.left,
				inRect.top - halfRadius,
				x2, y1 - halfRadius,

	}

	fast_float angle = UMath::NormalizeAngle(UMath::ArcTangent(dy / dx));
	


	fast_float cosA = UMath::Cosine(angle);
	fast_float sinA = UMath::Sine(angle);
	fast_float len = UMath::SquareRoot(dx * dx + dy * dy);
	fast_float offsX = adjustedRadius * -sinA;
	fast_float offsY = 
}


uint32 UGraphics::ScaleColor(uint32 inColor, int32 inFactor)
{
	return (((inColor >> 16 & 255) * inFactor) / 255 & 255) << 16 |
		(((inColor >> 8 & 255) * inFactor) / 255 & 255) << 8 |
		((inColor >> 24) * inFactor) / 255 << 24;
}
