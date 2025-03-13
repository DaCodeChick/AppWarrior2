#include "../include/UTimer.hpp"
#include "../include/UMemory.hpp"

struct STimer
{
	uint32 signature;
	uint32 id;
	bool once;
};


TTimer UTimer::StartNew()
{
	STimer *tm = (STimer *)UMemory::NewClear(sizeof(STimer));

	return (TTimer)tm;
}
