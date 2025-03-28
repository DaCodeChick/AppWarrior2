#include "../include/UError.hpp"
#include "../include/UMemory.hpp"

#ifdef _MACINTOSH
#include <MacMemory.h>
#endif // _MACINTOSH

#ifndef _WIN32 || !defined(_MACINTOSH)
#include <cstdlib>
#endif // _WIN32


static bool _gInitialized = false;
static Size _gAllocCount = 0;

#ifdef _WIN32
static HANDLE _gHeap = NULL;
#endif // _WIN32


uint32 UMemory::Checksum(const void *inData, Size inDataSize, uint32 inInit)
{
	#define PRIME 0x1000193

	const uint8 *dp = CBPTR(inData);

	while (inDataSize && (ADDR_CAST(inData) & 3U))
	{
		inInit = inInit * PRIME ^ *dp++; 
		inDataSize--;
	}

	const uint32 *dp32 = CDPTR(inData);
	for (; inDataSize >= 4; inDataSize -= 4)
		inInit = inInit * PRIME ^ swap_int(*dp32++);
	
	dp = CBPTR(dp32);
	while (inDataSize--)
		inInit = inInit * PRIME ^ *dp++;
	
	return inInit;
}


void UMemory::Clear(void *outDest, Size inSize)
{
	if (!outDest || !inSize) return;
#ifdef _MACINTOSH
	BlockZero(outDest, inSize);
#else
	uint8 *p = BPTR(outDest);
	const uintptr misalign = ADDR_CAST(p) & PTR_BITMASK;

	if (misalign)
	{
		const Size adjust = PTR_BITS - misalign;
		const Size init = min(adjust, inSize);
		Fill(p, 0, (uint8)init);
		p += init;
		inSize -= init;
	}

	if (inSize >= PTR_BITS)
	{
		const Size chunks = inSize >> PTR_BITS;
		inSize &= PTR_BITMASK;
		Size *zp = ZPTR(p);

		for (Size i = 0; i < chunks; ++i)
		{
			for (Size j = 0; j < PTR_ALIGN; ++j)
				zp[j] = 0;
		}
		p = BPTR(zp);
	}

	for (Size i = 32; i > 2; i >>= 1)
	{
		Fill(p, inSize & i, (uint32)0);
		p += i;
	}
	if (inSize & 2)
	{
		Fill(p, sizeof(uint16), (uint16)0);
		p += 2;
	}
	if (inSize & 1)
		*p = 0;
#endif
}


uint32 UMemory::CRC(const void *inData, Size inDataSize, uint32 inInit)
{
	static const uint32 ccitt32_crctab[256] = {
		0, 0x4C11DB7, 0x9823B6E, 0xD4326D9,
		0x130476DC, 0x17C56B6B, 0x1A864DB2, 0x1E475005,
		0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61,
		0x350C9B64, 0x31CD86D3, 0x3C8EA00A, 0x384FBDBD,
		0x4C11DB70, 0x48D0C6C7, 0x4593E01E, 0x4152FDA9,
		0x5F15ADAC, 0x5BD4B01B, 0x569796C2, 0x52568B75,
		0x6A1936C8, 0x6ED82B7F, 0x639B0DA6, 0x675A1011,
		0x791D4014, 0x7DDC5DA3, 0x709F7B7A, 0x745E66CD,
		0x9823B6E0, 0x9CE2AB57, 0x91A18D8E, 0x95609039,
		0x8B27C03C, 0x8FE6DD8B, 0x82A5FB52, 0x8664E6E5,
		0xBE2B5B58, 0xBAEA46EF, 0xB7A96036, 0xB3687D81,
		0xAD2F2D84, 0xA9EE3033, 0xA4AD16EA, 0xA06C0B5D,
		0xD4326D90, 0xD0F37027, 0xDDB056FE, 0xD9714B49,
		0xC7361B4C, 0xC3F706FB, 0xCEB42022, 0xCA753D95,
		0xF23A8028, 0xF6FB9D9F, 0xFBB8BB46, 0xFF79A6F1,
		0xE13EF6F4, 0xE5FFEB43, 0xE8BCCD9A, 0xEC7DD02D,
		0x34867077, 0x30476DC0, 0x3D044B19, 0x39C556AE,
		0x278206AB, 0x23431B1C, 0x2E003DC5, 0x2AC12072,
		0x128E9DCF, 0x164F8078, 0x1B0CA6A1, 0x1FCDBB16,
		0x18AEB13, 0x54BF6A4, 0x808D07D, 0xCC9CDCA,
		0x7897AB07, 0x7C56B6B0, 0x71159069, 0x75D48DDE,
		0x6B93DDDB, 0x6F52C06C, 0x6211E6B5, 0x66D0FB02,
		0x5E9F46BF, 0x5A5E5B08, 0x571D7DD1, 0x53DC6066,
		0x4D9B3063, 0x495A2DD4, 0x44190B0D, 0x40D816BA,
		0xACA5C697, 0xA864DB20, 0xA527FDF9, 0xA1E6E04E,
		0xBFA1B04B, 0xBB60ADFC, 0xB6238B25, 0xB2E29692,
		0x8AAD2B2F, 0x8E6C3698, 0x832F1041, 0x87EE0DF6,
		0x99A95DF3, 0x9D684044, 0x902B669D, 0x94EA7B2A,
		0xE0B41DE7, 0xE4750050, 0xE9362689, 0xEDF73B3E,
		0xF3B06B3B, 0xF771768C, 0xFA325055, 0xFEF34DE2,
		0xC6BCF05F, 0xC27DEDE8, 0xCF3ECB31, 0xCBFFD686,
		0xD5B88683, 0xD1799B34, 0xDC3ABDED, 0xD8FBA05A,
		0x690CE0EE, 0x6DCDFD59, 0x608EDB80, 0x644FC637,
		0x7A089632, 0x7EC98B85, 0x738AAD5C, 0x774BB0EB,
		0x4F040D56, 0x4BC510E1, 0x46863638, 0x42472B8F,
		0x5C007B8A, 0x58C1663D, 0x558240E4, 0x51435D53,
		0x251D3B9E, 0x21DC2629, 0x2C9F00F0, 0x285E1D47,
		0x36194D42, 0x32D850F5, 0x3F9B762C, 0x3B5A6B9B,
		0x315D626, 0x7D4CB91, 0xA97ED48, 0xE56F0FF,
		0x1011A0FA, 0x14D0BD4D, 0x19939B94, 0x1D528623,
		0xF12F560E, 0xF5EE4BB9, 0xF8AD6D60, 0xFC6C70D7,
		0xE22B20D2, 0xE6EA3D65, 0xEBA91BBC, 0xEF68060B,
		0xD727BBB6, 0xD3E6A601, 0xDEA580D8, 0xDA649D6F,
		0xC423CD6A, 0xC0E2D0DD, 0xCDA1F604, 0xC960EBB3,
		0xBD3E8D7E, 0xB9FF90C9, 0xB4BCB610, 0xB07DABA7,
		0xAE3AFBA2, 0xAAFBE615, 0xA7B8C0CC, 0xA379DD7B,
		0x9B3660C6, 0x9FF77D71, 0x92B45BA8, 0x9675461F,
		0x8832161A, 0x8CF30BAD, 0x81B02D74, 0x857130C3,
		0x5D8A9099, 0x594B8D2E, 0x5408ABF7, 0x50C9B640,
		0x4E8EE645, 0x4A4FFBF2, 0x470CDD2B, 0x43CDC09C,
		0x7B827D21, 0x7F436096, 0x7200464F, 0x76C15BF8,
		0x68860BFD, 0x6C47164A, 0x61043093, 0x65C52D24,
		0x119B4BE9, 0x155A565E, 0x18197087, 0x1CD86D30,
		0x29F3D35, 0x65E2082, 0xB1D065B, 0xFDC1BEC,
		0x3793A651, 0x3352BBE6, 0x3E119D3F, 0x3AD08088,
		0x2497D08D, 0x2056CD3A, 0x2D15EBE3, 0x29D4F654,
		0xC5A92679, 0xC1683BCE, 0xCC2B1D17, 0xC8EA00A0,
		0xD6AD50A5, 0xD26C4D12, 0xDF2F6BCB, 0xDBEE767C,
		0xE3A1CBC1, 0xE760D676, 0xEA23F0AF, 0xEEE2ED18,
		0xF0A5BD1D, 0xF464A0AA, 0xF9278673, 0xFDE69BC4,
		0x89B8FD09, 0x8D79E0BE, 0x803AC667, 0x84FBDBD0,
		0x9ABC8BD5, 0x9E7D9662, 0x933EB0BB, 0x97FFAD0C,
		0xAFB010B1, 0xAB710D06, 0xA6322BDF, 0xA2F33668,
		0xBCB4666D, 0xB8757BDA, 0xB5365D03, 0xB1F740B4
	};


	if (!inData || !inDataSize)
		return inInit;
	
	const uint8 *dp = CBPTR(inData);
	uintptr da = ADDR_CAST(inData);

	uint32 align = (uint32)(-da & 3);
	if (inDataSize < align)
		align = inDataSize;
	
	// unaligned bytes
	for (uint32 i = 0; i < align; i++)
		inInit = (inInit << 8) ^ ccitt32_crctab[(inInit >> 24) ^ *dp++];
	inDataSize -= align;

	// 4 byte aligned
	Size chunks = inDataSize >> 2;
	for (Size i = 0; i < chunks; i++)
		for (Size j = 0; j < 32; j += 8)
			inInit = (inInit << 8) ^ ccitt32_crctab[(inInit >> 24) ^
				((*CDPTR(dp) >> j) & 255)];
	
	// remaining bytes
	Size remain = inDataSize & 3;
	for (Size i = 0; i < remain; i++)
		inInit = (inInit << 8) ^ ccitt32_crctab[(inInit >> 24) ^ *dp++];
	
	return inInit;
}


void UMemory::Dispose(THdl inHdl)
{
#ifdef _WIN32
	if (inHdl) GlobalFree((HGLOBAL)inHdl);
#elif defined(_MACINTOSH)
	if (*inHdl) DisposePtr(*(Ptr)inHdl);
#else
	if (*inHdl) free(*inHdl);
#endif // _WIN32
	inHdl = NULL;
	_gAllocCount--;
}


void UMemory::Dispose(TPtr inPtr)
{
	if (!_gInitialized && !inPtr) return;
	if (inPtr)
#ifdef _WIN32
		HeapFree(_gHeap, 0, inPtr);
#elif defined(_MACINTOSH)
		DisposePtr((Ptr)inPtr);
#else
		free(inPtr);
#endif // _WIN32
	inPtr = NULL;
	_gAllocCount--;
}


void UMemory::Fill(void *outDest, Size inSize, uint8 inByte)
{
	if (!inSize || !outDest) return;

	const uint32 pat32 = inByte | (inByte << 8) | (inByte << 16) | (inByte << 24);
#ifdef BITS_64
	uint64 pat64 = pat32 | (pat32 << 32);
#endif // BITS_64

	if (inSize < PTR_ALIGN)
	{
		uint8 *dest = BPTR(outDest);
		while (inSize--)
			*dest++ = inByte;
		return;
	}

	uintptr misalign = ADDR_CAST(outDest) & PTR_ALIGN_MASK;
	if (misalign)
	{
		uint8 *dest = BPTR(outDest);
		uintptr adjust = PTR_ALIGN - misalign;

		while (misalign++ < PTR_ALIGN && inSize--)
			*dest++ = inByte;
		outDest = dest;
	}

	uintptr *baddr = (uintptr *)outDest;
#ifdef BITS_64
	Size count = inSize >> 3;
#else
	Size count = inSize >> 2;
#endif // BIT_64
	while (count--)
#ifdef BITS_64
		*baddr++ = pat64;
#else
		*baddr++ = pat32;
#endif // BIT_64

	uint8 *rp = BPTR(baddr);
	Size remain = inSize & PTR_ALIGN_MASK;
	while (remain--)
		*rp++ = inByte;
}


void UMemory::Fill(void *outDest, Size inSize, uint16 inWord)
{
	if (!inSize || !outDest) return;

	const uint32 pat32 = inWord | (inWord << 16);
#ifdef BITS_64
	const uint64 pat64 = pat32 | (pat32 << 32);
#endif // BITS_64

	uint8 *bp = BPTR(outDest);
	if (inSize == 1)
	{
		*bp = (uint8)(inWord & 255);
		return;
	}

	uint16 *wp = WPTR(bp);
	const Size count = inSize >> 1;

	if (count >= PTR_ALIGN)
	{
		const uintptr misalign = ADDR_CAST(wp) & PTR_ALIGN_MASK;
		
		if (misalign)
		{
			const uintptr adjust = (PTR_ALIGN - misalign) >> 1;
			const Size init = min(adjust, count);

			for (uintptr i = 0; i < init; ++i)
				*wp++ = inWord;
			inSize -= init << 1;
			if (!inSize) return;
		}

		uintptr *waddr = (uintptr *)wp;
		const Size words = (inSize >> 1) >> (PTR_ALIGN >> 1);
#ifdef BITS_32
		const uintptr pat = pat32;
#else
		const uintptr pat = pat64;
#endif
		for (Size i = 0; i < words; ++i)
			*waddr++ = pat;
		
		wp = WPTR(waddr);
		const Size rem = inSize >> 1;

		for (Size i = 0; i < rem; ++i)
			*wp++ = inWord;
		
		// remaining misaligned byte
		if (inSize & 1)
		{
			bp = BPTR(wp);
			*bp = (uint8)(inWord & 255);
		}
	}
}


void UMemory::Fill(void *outDest, Size inSize, uint32 inLong)
{
	if (!inSize || !outDest) return;

#ifdef BITS_64
	const uint64 pat64 = inLong | (inLong << 32);
#endif // BITS_64
	uint8 *bp = BPTR(outDest);
	if (inSize == 1)
	{
		*bp = (uint8)(inLong & 255);
		return;
	}

	uint16 *wp = WPTR(bp);
	if (inSize == 2)
	{
		*wp = (uint16)(inLong & 65535);
		return;
	}

	if (inSize == 3)
	{
		*wp = (uint16)(inLong & 65535);
		bp = BPTR(wp);
		*bp = (uint8)((inLong & 0xFF0000) >> 16);
		return;
	}

	uint32 *lp = DPTR(outDest);
	const Size count = inSize >> 1;

	if (count >= PTR_ALIGN)
	{
		const uintptr misalign = ADDR_CAST(lp) & PTR_ALIGN_MASK;
		
		if (misalign)
		{
			const uintptr adjust = (PTR_ALIGN - misalign) >> 1;
			const Size init = min(adjust, count);

			for (uintptr i = 0; i < init; ++i)
				*lp++ = inLong;
			inSize -= init << 1;
			if (!inSize) return;
		}

		uintptr *laddr = (uintptr *)lp;
		const Size longs = (inSize >> 2) >> (PTR_ALIGN >> 1);
#ifdef BITS_32
		const uintptr pat = inLong;
#else
		const uintptr pat = pat64;
#endif
		for (Size i = 0; i < longs; ++i)
			*laddr++ = pat;
		
		lp = DPTR(laddr);
		const Size rem = inSize >> 1;

		for (Size i = 0; i < rem; ++i)
			*lp++ = inLong;
		
		wp = WPTR(lp);
		// remaining misaligned word
		if (inSize & 2)
			*wp = (uint16)(inLong & 65535);
		
		bp = BPTR(wp);
		// remaining misaligned byte
		if (inSize & 1)
			*bp = (uint8)((inLong & 0xFF0000) >> 16);
}


void UMemory::Init()
{
	_gInitialized = true; // no need to safeguard this (yet?)
#ifdef _WIN32
	_gHeap = GetProcessHeap();
#endif // _WIN32
}


Size UMemory::Move(void *ioDest, const void *inSrc, Size inSize)
{
#ifdef _WIN32
#elif defined(_MACINTOSH)
	BlockMoveData(inSrc, ioDest, inSize);
#else
	memmove(ioDest, inSrc, inSize);
#endif
	return inSize;
}


TPtr UMemory::New(Size inSize)
{
	if (!inSize) ; // error_Param
#ifdef _WIN32
	HANDLE p = HeapAlloc(_gHeap, 0, inSize);
#elif defined(_MACINTOSH)
	Ptr p = NewPtr(inSize);
#else
	void *p = malloc(inSize);
#endif // _WIN32
	if (!p) ; // memoryError_NotEnough
	_gAllocCount++;

	return (TPtr)p;
}


TPtr UMemory::NewClear(Size inSize)
{
	if (!inSize) ; // error_Param
#ifdef _WIN32
	HANDLE p = HeapAlloc(_gHeap, HEAP_ZERO_MEMORY, inSize);
#elif defined(_MACINTOSH)
	Ptr p = NewPtrClear(inSize);
#else
	void *p = malloc(inSize);
	if (!p) ; // memoryError_NotEnough
		Clear(p, inSize);
#endif // _WIN32
	_gAllocCount++;

	return (TPtr)p;
}


THdl UMemory::NewHandle(Size inSize)
{
	if (!inSize) ; // error_Param
#ifdef _WIN32
	HGLOBAL h = GlobalAlloc(GMEM_FIXED, inSize);
	if (!h) ; // memoryError_NotEnough
#elif defined(_MACINTOSH)
#else
#endif // _WIN32
	_gAllocCount++;
	return (THdl)h;
}


THdl UMemory::NewHandleClear(Size inSize)
{
	if (!inSize) ; // error_Param
#ifdef _WIN32
	HGLOBAL h = GlobalAlloc(GMEM_ZEROINIT, inSize);
#elif defined(_MACINTOSH)
#else
#endif // _WIN32
	if (!h) ; // memoryError_NotEnough
	_gAllocCount++;
	return (THdl)h;
}


TPtr UMemory::Reallocate(TPtr inPtr, uint32 inSize)
{
#ifdef _WIN32
#elif defined(_MACINTOSH)
#else
	void *p;
#endif // _WIN32

	if (!inPtr)
	{
#ifdef _WIN32
#elif defined(_MACINTOSH)
#else
		p = malloc(inSize);
#endif // _WIN32
		if (!p) ; // memoryError_NotEnough
		_gAllocCount++;
	}
	else if (!inSize)
	{
#ifdef _WIN32
#elif defined(_MACINTOSH)
#else
		free(p);
#endif // _WIN32
		p = NULL;
		_gAllocCount--;
	}
	else
	{
#ifdef _WIN32
#elif defined(_MACINTOSH)
#else
		p = realloc(inSize);
#endif // _WIN32
		if (!p) ; // memoryError_NotEnough
	}

	return (TPtr)p;
}
