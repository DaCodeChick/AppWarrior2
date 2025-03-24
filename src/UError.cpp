#include "../include/UError.hpp"
#include "../include/UFileSys.hpp"
#include "../include/UMemory.hpp"
#include "../include/UNetwork.hpp"

#ifdef _WIN32
#include <winsock.h>
#elif defined(_MACINTOSH)
#include <MacErrors.h>
#else
#endif // _WIN32

#ifdef _WIN32
uint32 UError::WinToGenError(DWORD inWinError)
{
	switch (inWinError)
	{
		case ERROR_INVALID_PARAMETER: return error_Param;
		case ERROR_NOT_ENOUGH_MEMORY: return memError_NotEnough;
		case ERROR_INVALID_BLOCK:
		case ERROR_INVALID_HANDLE:
			return memError_BlockInvalid;
		case ERROR_FILE_NOT_FOUND: return fsError_NoSuchItem;
		case ERROR_ALREADY_EXISTS: return fsError_ItemAlreadyExists;
		case ERROR_INVALID_NAME:
		case ERROR_FILENAME_EXCED_RANGE:
			return fsError_PathTooLong;
		case WSAHOST_NOT_FOUND:
		case WSATRY_AGAIN:
		case WSANO_DATA:
			return tptError_BadAddress;
		case WSAENOBUFS:
		case WSAETOOMANYREFS:
			return tptError_BadData;
		case WSAEADDRINUSE: return tptError_AddressInUse;
		case WSAECONNRESET: return tptError_ConnectionReset;
		case WSAECONNREFUSED: return tptError_ConnectionRefused;
		case WSAETIMEDOUT: return tptError_ConnectionTimedOut;
		case WSAENETRESET:
		case WSAECONNABORTED:
		case WSAEHOSTDOWN:
			return tptError_ConnectionClosed;
		case WSAENETDOWN:
		case WSAENETUNREACH:
		case WSAEHOSTUNREACH:
			return tptError_HostUnreachable;
		default: return error_Unknown;
	}
}
#elif defined(_MACINTOSH)
uint32 UError::MacToGenError(OSErr inMacError)
{
	switch (inMacError)
	{
		case errFSNameTooLong: return fsError_PathTooLong;
		case kECONNABORTEDErr: return tptError_ConnectionClosed;
		case kENETDOWNErr:
		case kEHOSTUNREACHErr:
			return tptError_HostUnreachable;
		default: return error_Unknown;
	}
}
#else
uint32 UError::StdToGenError(int inError)
{
	switch (inError)
	{
		default: return error_Unknown;
	}
}
#endif // _WIN32
