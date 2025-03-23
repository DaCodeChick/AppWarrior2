#pragma once

#include "typedefs.hpp"

#define LL_HIGHPART(x) ((uint64)(x) >> 32)
#define LL_LOWPART(x) ((uint64)(x) % 0xFFFFFFFFULL)


class HXAPI UMath
{
public:
	static uint32 CalcRandomSeed();
	static uint32 Calculate(const void *inData, Size inDataSize, uint32 inInit);
	static uint32 GetRandom();

	static uint64 Div64U(uint64 inA, uint64 inB);

	static fast_float ArcTangent(fast_float x);
	static fast_float Cosine(fast_float x);
	static fast_float NormalizeAngle(fast_float x);
	static fast_float Sine(fast_float x);
	static fast_float SquareRoot(fast_float x);
};
