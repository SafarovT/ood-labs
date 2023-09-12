#include "../StrategyFn.h"
#include <iostream>

Strategy FlyWithWings()
{
	unsigned flightsCount = 0;
	std::cout << "I'm flying with wings!!" << std::endl;

	return [&]() mutable
	{
		flightsCount++;
		std::cout << "Flight number: " << flightsCount << std::endl
			<< "I'm flying with wings!!" << std::endl;
	};
}