#pragma once

#include "typedefs.hpp"

/** @brief Error */
struct SError
{
};


class HXAPI UError
{
public:
#ifdef _MACINTOSH
	static uint32 MacToGenError(OSErr inMacError);
#elif defined(_WIN32)
	static uint32 WinToGenError(DWORD inWinError);
#else
	static uint32 StdToGenError(int inError);
};


enum
{
	error_Param = 0x10002,
	error_Signature = 0x10019,
	error_Unknown = 0x1001B
};
