#include "../include/UCryptTransact.hpp"


uint32 UCryptTransact::Crypt(uint32 inKey, const void *ioData, Size inSize)
{
	uint32 *dp32 = (uint32 *)ioData;
	
	inSize >>= 2;
	for (Size i = 0; i < inSize; i++)
	{
		inKey = (inKey << 1) + 0x4878; // 'Hx'
		dp32[i] ^= swap_int(inKey);
	}

	return inKey;
}
