#pragma once
#include "../StrategyFn.h"
#include <iostream>

FlyStrategy MakeFlyWithWings()
{
	unsigned flightsCount = 0;

	return [flightsCount]() mutable -> void
	{
		flightsCount++;
		std::cout << "Flight number: " << flightsCount << std::endl
			<< "I'm flying with wings!!" << std::endl;
	};
}