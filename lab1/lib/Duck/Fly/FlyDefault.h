#ifndef FLYDEFAULT_H
#define FLYDEFAULT_H

#include "IFlyBehavior.h"

class FlyDefault : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flightsCount++;
		std::cout << "Fligth number: " << m_flightsCount << std::endl;
	}
private:
	unsigned int m_flightsCount = 0;
};

#endif