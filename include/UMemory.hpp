#pragma once

#include "typedefs.hpp"

typedef class TPtrObj *TPtr;
typedef class THdlObj *THdl;

/** @brief Memory manager */
class HXAPI UMemory
{
public:
	static void Init();
	
	static void Dispose(TPtr inPtr);
	static TPtr New(Size inSize);
	static TPtr NewClear(Size inSize);

	static void Dispose(THdl inHdl);
	static THdl NewHandle(Size inSize);
	static THdl NewHandle(const void *inData, Size inSize);
	static THdl NewHandleClear(Size inSize);

	static uint32 Checksum(const void *inData, Size inDataSize, uint32 inInit);
	static uint32 CRC(const void *inData, Size inDataSize, uint32 inInit);

	static void Clear(void *outDest, Size inSize);
	static void Fill8(void *outDest, Size inSize, uint8 inByte);
	static void Fill16(void *outDest, Size inSize, uint16 inWord);
	static void Fill32(void *outDest, Size inSize, uint32 inLong);
	static Size Move(void *ioDest, const void *inSrc, Size inSize);

	static void Fill(void *outDest, Size inSize, uint8 inByte)
	{
		Fill8(outDest, inSize, inByte);
	}
};


enum
{
	memError_NotEnough = 0x20065,
	memError_BlockInvalid
};


class HXAPI TPtrObj
{
public:
	void operator delete(void *p)
	{
		UMemory::Dispose((TPtr)p);
	}
protected:
	TPtrObj()
	{
	}
};


class HXAPI THdlObj
{
public:
	void operator delete(void *p)
	{
		UMemory::Dispose((THdl)p);
	}
protected:
	THdlObj()
	{
	}
};
