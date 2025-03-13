#pragma once

#include "typedefs.hpp"

enum
{
	netError_BadAddress = 0x40067,
	netError_BadData,
	netError_AddressInUse,
	netError_ConnectionReset,
	netError_ConnectionRefused,
	netError_ConnectionTimedOut,
	netError_ConnectionClosed,
	netError_HostUnreachable = 0x4006F
};


class HXAPI UNetwork
{
public:
	static void Init();
	static void Deinit();
};
