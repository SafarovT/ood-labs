#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyNoWay.h"
#include "Quack/MuteQuackBehavior.h"
#include "Strategy/Dance/DanceStayStill.h"
#include <iostream>
#include <memory>

class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(
			FlyNoWay,
			std::make_unique<MuteQuackBehavior>(),
			DanceStayStill
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};

#endif
