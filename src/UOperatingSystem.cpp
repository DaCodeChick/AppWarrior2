#include "../include/UOperatingSystem.hpp"

#ifdef _WIN32
static HINSTANCE _gProgramInstance = NULL;


HINSTANCE UOperatingSystem::GetProgramInstance()
{
	return _gProgramInstance;
}


void UOperatingSystem::Init(HINSTANCE hInstance, LPCSTR lpszCmdLine)
{
	_gProgramInstance = hInstance;
}

#endif // _WIN32
