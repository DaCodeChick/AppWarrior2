#include "../include/GrafTypes.hpp"


void SRect::Constrain(const SRect &inMax)
{
	if (top < inMax.top) top = inMax.top;
	else if (top > inMax.bottom) top = inMax.bottom;

	if (left < inMax.left) left = inMax.left;
	else if (left > inMax.right) left = inMax.right;

	if (bottom > inMax.bottom) bottom = inMax.bottom;
	else if (bottom < inMax.top) bottom = inMax.top;

	if (right > inMax.right) right = inMax.right;
	else if (right < inMax.left) right = inMax.left;
}


bool SRect::GetIntersection(const SRect &inRect, SRect &outSect) const
{
	outSect.left = max(left, inRect.left);
	outSect.top = max(top, inRect.top);
	outSect.right = min(right, inRect.right);
	outSect.bottom = min(bottom, inRect.bottom);

	if ((outSect.left < outSect.right) && (outSect.top < outSect.bottom))
		return true;
	
	outSect.SetEmpty();
	return false;
}


void SRect::GetUnion(const SRect &inRect, SRect &outUnion) const
{
	outUnion.top = min(top, inRect.top);
	outUnion.left = min(left, inRect.left);
	outUnion.bottom = max(bottom, inRect.bottom);
	outUnion.right = max(right, inRect.right);
}


bool SRect::Intersects(const SRect &inRect) const
{
	return (max(left, inRect.left) < min(right, inRect.right)) &&
		(max(top, inRect.top) < min(bottom, inRect.bottom));
}
