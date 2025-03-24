#include "../include/UMemory.hpp"
#include "../include/UMessageSys.hpp"
#include "../include/UOperatingSystem.hpp"
#include "../include/URegularTransport.hpp"

#ifdef _WIN32
#include <winsock.h>
#endif

static bool _gInitialized = false;

#ifdef _WIN32
static ATOM _gTptClassAtom = 0;
#endif


void URegularTransport::Deinit()
{
	UMessageSys::Deinit();
#ifdef _WIN32
	WSACleanup();
#endif
}


void URegularTransport::Init()
{
	if (_gInitialized) return;

	UMessageSys::Init();

#ifdef _WIN32
	WSADATA wsaData;

	if (!_gTptClassAtom)
	{
		WNDCLASSEXA wndClass;

		UMemory::Clear(&wndClass, sizeof(WNDCLASSEXA);
		wndClass.hInstance = UOperatingSystem::GetProgramInstance();
		wndClass.cbSize = sizeof(WNDCLASSEXA);
		//wndClass.lpfnWndProc =
		wndClass.lpszClassName = "%%stdwinsockclass%%";

		_gTptClassAtom = RegisterClassExA(&wndClass);
	}

	WSAStartup(MAKEWORD(1, 1), &wsaData);
#endif

	_gInitialized = true;
}
