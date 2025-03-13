#include "../include/UUserInterface.hpp"
#include "../include/UMemory.hpp"


SAppearance * UUserInterface::NewAppearance()
{
	SAppearance *app = (SAppearance *)UMemory::NewClear(sizeof(SAppearance));
	return app;
}
