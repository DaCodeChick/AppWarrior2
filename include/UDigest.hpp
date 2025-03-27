#pragma once

#include "typedefs.hpp"
#include "_mwexpon.h"

class HXAPI UDigest
{
	/** @brief Encode in MD5 format */
	static void * MD5_Encode(void *inData, Size inDataSize, uint32 &outDataSize);
};

#include "_mwexpoff.h"
