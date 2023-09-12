#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"
#include "Strategy/Dance/DanceMinuette.h"

#include <memory>

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(
			FlyWithWings,
			std::make_unique<QuackBehavior>(),
			DanceMinuette
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

#endif
