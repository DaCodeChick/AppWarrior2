#include "../include/ANSI.h"

#ifdef _MACINTOSH
#include <PLStringFuncs.h>
#endif


int pstrcat(unsigned char *dst, const unsigned char *src)
{
#ifdef _MACINTOSH
	PLstrcat(dst, src);
#else
#endif
	return dst[0];
}


unsigned char * pstrchr(const unsigned char *str, int c)
{
#ifdef _MACINTOSH
	return (unsigned char *)PLstrchr(str, (short)c);
#else
#endif
}


int pstrcmp(const unsigned char *str1, const unsigned char *str2)
{
#ifdef _MACINTOSH
	return PLstrcmp(str1, str2);
#else
#endif
}


int pstrcpy(unsigned char *dst, const unsigned char *src)
{
#ifdef _MACINTOSH
	PLstrcpy(dst, src);
#else
#endif
	return dst[0];
}


int pstrncpy(unsigned char *dst, const unsigned char *src, int len)
{
#ifdef _MACINTOSH
	PLstrncpy(dst, src, (short)len);
#else
#endif
	return dst[0];
}


unsigned char * pstrrchr(const unsigned char *str, int c)
{
#ifdef _MACINTOSH
	return (unsigned char *)PLstrrchr(str, (short)c);
#else
#endif
}


HXAPI void pstrrev(unsigned char *str)
{
#ifdef _MACINTOSH
#elif defined(_WIN32)
#else
#endif
}
