#include "../include/UMemory.hpp"

#include <cstring>
#include <print>

int main(int argc, char **argv)
{
	if (argc != 2) return -1;

	std::println("UMemory::CRC:\t{:08X}",
		UMemory::CRC(argv[1], strlen(argv[1]), 0xDEADBEEF));
	std::println("UMemory::Checksum:\t{:08X}",
		UMemory::Checksum(argv[1], strlen(argv[1]), 0xDEADBEEF));
	
	return 0;
}
