#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyNoWay.h"
#include "Strategy/Quack/Squeak.h"
#include "Strategy/Dance/DanceStayStill.h"
#include <iostream>

class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(
			FlyNoWay,
			Squeak,
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
