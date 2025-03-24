#pragma once

#include "typedefs.hpp"

enum
{
	tptError_BadAddress = 0x40067,
	tptError_BadData,
	tptError_AddressInUse,
	tptError_ConnectionReset,
	tptError_ConnectionRefused,
	tptError_ConnectionTimedOut,
	tptError_ConnectionClosed,
	tptError_HostUnreachable = 0x4006F
};


class HXAPI URegularTransport
{
public:
	static void Init();
	static void Deinit();
};
