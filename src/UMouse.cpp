#include "../include/UMouse.hpp"

#ifdef _MACINTOSH
#include <Events.h>
#endif // _MACINTOSH


#define NUM_CURSORS 17

static int32 _gCurCursorID = 0;

#ifdef _WIN32
static HCURSOR _gCursors[NUM_CURSORS] = {
	NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL
};
#endif // _WIN32


uint32 UMouse::GetDoubleClickTime()
{
#ifdef _WIN32
	return ::GetDoubleClickTime();
#elif defined(_MACINTOSH)
	return (GetDblTime() * 50) / 3;
#else
#endif // _WIN32
}


int32 UMouse::GetImage()
{
	return _gCurCursorID;
}


void UMouse::GetLocation(SPoint &outLoc)
{
#ifdef _WIN32
	GetCursorPos((LPPOINT)&outLoc);
#elif defined(_MACINTOSH)
	Point p;

	GetGlobalMouse(&p);
	outLoc.x = p.h;
	outLoc.y = p.v;
#else
#endif // _WIN32
}


void UMouse::SetImage(int32 inID)
{
	if (_gCurCursorID == inID) return;
	
#ifdef _WIN32
	if (!_gCursors)
	{
		_gCursors[0] = LoadCursorW(NULL, IDC_ARROW);
		_gCursors[1] = _gCursors[0];
		_gCursors[2] = LoadCursorW(NULL, IDC_IBEAM);
		_gCursors[3] = LoadCursorW(NULL, IDC_CROSS);
		_gCursors[4] = _gCursors[3];
		_gCursors[5] = LoadCursorW(NULL, IDC_WAIT);
		_gCursors[6] = LoadCursorW(NULL, IDC_NO);
		_gCursors[7] = LoadCursorW(NULL, IDC_SIZE);
		_gCursors[8] = LoadCursorW(NULL, IDC_SIZEWE);
		_gCursors[9] = LoadCursorW(NULL, IDC_SIZENS);
		_gCursors[10] = LoadCursorW(NULL, IDC_SIZENWSE);
		_gCursors[11] = LoadCursorW(NULL, IDC_SIZENESW);
		_gCursors[12] = _gCursors[0];
		_gCursors[13] = _gCursors[0];
		_gCursors[14] = _gCursors[0];
		_gCursors[15] = _gCursors[0];
		_gCursors[16] = _gCursors[0];
	}

	if (inID >= NUM_CURSORS)
		inID = 0;

	SetCursor(_gCursors[inID]);
	_gCurCursorID = inID;
#endif // _WIN32
}
