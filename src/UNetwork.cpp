#include "../include/UMessageSys.hpp"
#include "../include/UNetwork.hpp"
#include "../include/UOperatingSystem.hpp"

#ifdef _WIN32
#include <winsock.h>
#endif

static bool _gInitialized = false;

#ifdef _WIN32
static ATOM _gNetClassAtom = 0;
#endif


void UNetwork::Deinit()
{
	UMessageSys::Deinit();
#ifdef _WIN32
	WSACleanup();
#endif
}


void UNetwork::Init()
{
	if (_gInitialized) return;

	UMessageSys::Init();

#ifdef _WIN32
	WSADATA wsaData;
	WNDCLASSEXA wndClass;

	if (!_gNetClassAtom)
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

		_gNetClassAtom = RegisterClassExA(&wndClass);
	}

	WSAStartup(MAKEWORD(1, 1), &wsaData);
#endif

	_gInitialized = true;
}
