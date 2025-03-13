#pragma once

#include "typedefs.hpp"

class HXAPI UOperatingSystem
{
public:
#ifdef _WIN32
	static void Init(HINSTANCE hInstance, LPCSTR lpszCmdLine);

	static HINSTANCE GetProgramInstance();
#endif // _WIN32
};
