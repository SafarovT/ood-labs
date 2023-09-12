#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyNoWay.h"
#include "Strategy/Quack/QuackBehavior.h"
#include "Strategy/Dance/DanceStayStill.h"

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(
			FlyNoWay,
			QuackBehavior,
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
