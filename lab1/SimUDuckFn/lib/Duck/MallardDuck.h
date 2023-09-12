#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Strategy/Fly/FlyWithWings.h"
#include "Strategy/Quack/QuackBehavior.h"
#include "Strategy/Dance/DanceWaltz.h"

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(
			MakeFlyWithWings(),
			QuackBehavior,
			DanceWaltz
		)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

#endif
