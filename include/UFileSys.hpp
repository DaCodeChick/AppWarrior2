#pragma once

#include "typedefs.hpp"

class TFSRefObj;

class HXAPI UFileSys
{
public:	
	static void Dispose(TFSRefObj *inRef);
	static void Open(TFSRefObj *inRef);
};


enum
{
	fsError_NoSuchItem = 0x30067,
	fsError_ItemAlreadyExists = 0x30073,
	fsError_PathToLong = 0x30076
};


/** @brief File system object interface */
class HXAPI TFSRefObj
{
public:
	void operator delete(void *p)
	{
		UFileSys::Dispose((TFSRefObj *)p);
	}
protected:
	TFSRefObj()
	{
	}
};
