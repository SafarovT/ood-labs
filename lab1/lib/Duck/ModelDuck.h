#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceStayStill.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(
			std::make_unique<FlyNoWay>(),
			std::make_unique<QuackBehavior>(),
			std::make_unique<DanceStayStill>()
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};

#endif
