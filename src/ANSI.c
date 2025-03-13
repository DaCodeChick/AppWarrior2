#include "../include/ANSI.h"

#ifdef _MACINTOSH
#include <PLStringFuncs.h>
#else
#include <string.h>
#endif


int pstrcat(unsigned char *dst, const unsigned char *src)
{
#ifdef _MACINTOSH
	PLstrcat(dst, src);
#else
	dst[0] += src[0] > 255 ? 255 : src[0];
	strncat((const char *)&dst[1], (const char *)&src[1], dst[0]);
#endif
	return dst[0];
}


int pstrcmp(const unsigned char *str1, const unsigned char *str2)
{
#ifdef _MACINTOSH
	return PLstrcmp(str1, str2);
#else
	return strncmp((const char *)&str1[1], (const char *)&str2[1], 255);
#endif
}


int pstrcpy(unsigned char *dst, const unsigned char *src)
{
#ifdef _MACINTOSH
	PLstrcpy(dst, src);
#else
	dst[0] = src[0];
	strncpy((char *)&dst[1], (const char *)&src[1], dst[0]);
#endif
	return dst[0];
}


int pstrncpy(unsigned char *dst, const unsigned char *src, int len)
{
#ifdef _MACINTOSH
	PLstrncpy(dst, src, (short)len);
#else
	dst[0] = len < src[0] ? len : src[0];
	strncpy((char *)&dst[1], (const char *)&src[1], dst[0]);
#endif
	return dst[0];
}


unsigned char * pstrrchr(const unsigned char *str, int c)
{
#ifdef _MACINTOSH
	return (unsigned char *)PLstrrchr(str, (short)c);
#else
	return (unsigned char *)strrchr((const char *)&str[1], c);
#endif
}
