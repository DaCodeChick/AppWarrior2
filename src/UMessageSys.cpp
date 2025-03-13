#include "../include/CPtrList.hpp"
#include "../include/UMessageSys.hpp"

static bool _gEnabled = false;
static CVoidPtrList _gMessageQueue;

#ifdef _WIN32
static CRITICAL_SECTION _gMutex;
static DWORD _gThreadID = 0;
#endif // _WIN32


void UMessageSys::Deinit()
{
	if (!_gEnabled) return;

	_gEnabled = false;
#ifdef _WIN32
	DeleteCriticalSection(&_gMutex);
	_gThreadID = 0;
#endif // _WIN32
}


bool UMessageSys::Execute(TMessageSys inSys)
{
	if (!_gEnabled) return false;

#ifdef _WIN32
	EnterCriticalSection(&_gMutex);
#endif // _WIN32

	//bool b = _gMessageQueue.mCurrent;

#ifdef _WIN32
	LeaveCriticalSection(&_gMutex);
	if (b) ;
		//return (bool)PostThreadMessageW(_gMessageThreadID
#endif // _WIN32
}


void UMessageSys::Init()
{
	if (_gEnabled) return;

	_gEnabled = true;
#ifdef _WIN32
	InitializeCriticalSection(&_gMutex);
	_gThreadID = GetCurrentThreadId();
#endif // _WIN32
}
