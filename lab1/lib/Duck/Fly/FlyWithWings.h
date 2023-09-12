#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flightsCount++;
		std::cout << "Fligth number: " << m_flightsCount << std::endl
			<< "I'm flying with wings!!" << std::endl;
	}
private:
	unsigned int m_flightsCount = 0;
};

#endif
