#include "../include/UMessageSys.hpp"
#include "../include/URegularTransport.hpp"
#include "../include/UOperatingSystem.hpp"

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
	WNDCLASSEXA wndClass;

	if (!_gTptClassAtom)
	{
		wndClass.hInstance = UOperatingSystem::GetProgramInstance();
		wndClass.cbSize = sizeof(WNDCLASSEXA);
		wndClass.style = 0;
		//wndClass.lpfnWndProc =
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hIcon = NULL;
		wndClass.hCursor = NULL;
		wndClass.hbrBackground = NULL;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = "%%stdwinsockclass%%";
		wndClass.hIconSm = NULL;

		_gTptClassAtom = RegisterClassExA(&wndClass);
	}

	WSAStartup(MAKEWORD(1, 1), &wsaData);
#endif

	_gInitialized = true;
}
