#include "Logger.h"

unsigned int Logger::clickCounter = 0;
HHOOK Logger::hmouseHook = HHOOK(0);

unsigned int Logger::GetClickCount() noexcept
{
	return clickCounter;
}

void PrintResults() noexcept
{
	while (true)
	{
		std::cout << "Mouse clicked " << Logger::GetClickCount()  << " times" << std::endl;
	}
}
