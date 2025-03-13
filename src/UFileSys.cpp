#include "../include/UFileSys.hpp"

struct SFileSysRef
{
	Handle h;
	uint32 typeID;
	char16 *path;
	uint32 pathSize;
	uint32 pathFlags;
	uint32 fileFlags;
	uint32 _unknown;
};


void UFileSys::Open(TFSRefObj *inRef)
{
	if (!inRef) ; // error_Param
	SFileSysRef *ref = (SFileSysRef *)inRef;
	if (ref->typeID != TypeID) ; // error_TypeID

#ifdef _WIN32
	ShellExecuteW(NULL, L"open", ref->path, NULL, L"C:\\", 1);
#elif defined(_MACINTOSH) // _WIN32
#else
#endif // _WIN32
}
