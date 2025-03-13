#pragma once

#include "typedefs.hpp"


/** @brief Point */
struct SPoint
{
	int32 x, y;
};


/** @brief Rectangle */
struct HXAPI SRect
{
	int32 left, top, right, bottom;

	void Constrain(const SRect &inMax);
	bool GetIntersection(const SRect &inRect, SRect &outSect) const;
	void GetUnion(const SRect &inRect, SRect &outUnion) const;
	bool Intersects(const SRect &inRect) const;

	void SetEmpty()
	{
		top = left = bottom = right = 0;
	}

#ifdef _WIN32
	operator RECT()
	{
		return *(RECT *)this;
	}
#endif // _WIN32
};


const fast_float gm_2Pi = 6.283185307179586;
const fast_float gm_Pi = 3.141592653589793;
