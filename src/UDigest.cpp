#include "../include/3rdparty/md5.h"
#include "../include/UDigest.hpp"
#include "../include/UMemory.hpp"

void * UDigest::MD5_Encode(void *inData, Size inDataSize, uint32 &outDataSize)
{
	MD5_CTX ctx;
	outDataSize = sizeof(uint8) << 4;
	void *digest = UMemory::New(outDataSize);

	MD5Init(&ctx);
	MD5Update(&ctx, BPTR(inData), inDataSize);
	MD5Final(BPTR(digest), &ctx);

	return digest;
}
