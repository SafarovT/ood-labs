#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyNoWay.h"
#include "Quack/SqueakBehavior.h"
#include "Strategy/Dance/DanceStayStill.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(
			FlyNoWay,
			std::make_unique<SqueakBehavior>(),
			DanceStayStill
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

#endif
