#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

class HXAPI CVoidPtrList
{
public:
	void AddItem(void *inData);
	void * RemoveItem();
	void RemoveItem(void *ioData);
protected:
	void *mHead, *mTail;
	int mOffset;
	uint32 mCount;
};

#include "_mwexpoff.h"
