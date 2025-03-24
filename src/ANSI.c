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


unsigned char * pstrchr(const unsigned char *str, int c)
{
#ifdef _MACINTOSH
	return (unsigned char *)PLstrchr(str, (short)c);
#else
	return (unsigned char *)memchr(&str[1], c, str[0]);
#endif
}


int pstrcmp(const unsigned char *str1, const unsigned char *str2)
{
#ifdef _MACINTOSH
	return PLstrcmp(str1, str2);
#else
	if (str1[0] != str2[0]) return -1;
	return strncmp((const char *)&str1[1], (const char *)&str2[1], minsize);
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
#endif
}


HXAPI void pstrrev(unsigned char *str)
{
#ifdef _MACINTOSH
#elif defined(_WIN32)
#else
#endif
}
