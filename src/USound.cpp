#include "../include/USound.hpp"

#ifdef _MACINTOSH
#include <Sound.h>
#endif

void USound::Beep()
{
#ifdef _WIN32
	MessageBeep(MB_OK);
#elif defined(_MACINTOSH)
	SysBeep(20);
#else
#endif // _WIN32
}
