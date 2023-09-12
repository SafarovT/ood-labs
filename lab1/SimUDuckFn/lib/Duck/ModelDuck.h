#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyNoWay.h"
#include "Quack/QuackBehavior.h"
#include "Strategy/Dance/DanceStayStill.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(
			FlyNoWay,
			std::make_unique<QuackBehavior>(),
			DanceStayStill
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};

#endif
