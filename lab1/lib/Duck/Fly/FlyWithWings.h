#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "FlyDefault.h"
#include <iostream>

class FlyWithWings : public FlyDefault
{
public:
	void Fly() override
	{
		FlyDefault::Fly();
		std::cout << "I'm flying with wings!!" << std::endl;
	}
};

#endif
