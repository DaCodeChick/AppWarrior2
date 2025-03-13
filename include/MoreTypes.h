#pragma once

#include "GrafTypes.hpp"


struct SKeyMsgData
{
	uint64 time;
	uint32 keyCode;
	uint32 mods;
	uint32 unicodeChar;
	uint16 ansiChar;
	uint16 reserved;
};


struct SMouseMsgData
{
	uint64 time;
	uint32 event;
	uint32 mods;
	SPoint loc;
	uint8 button;
	uint8 reserved;
	uint16 misc;
};
