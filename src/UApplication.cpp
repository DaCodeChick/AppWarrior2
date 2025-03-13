#include "../include/UApplication.hpp"

static uint8 _gStateBuffer[256];


uint8 * UApplication::GetStateBuffer()
{
	return _gStateBuffer;
}
