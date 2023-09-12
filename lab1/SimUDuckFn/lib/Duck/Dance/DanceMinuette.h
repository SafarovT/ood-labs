#ifndef DANCEMINUETTE_H
#define DANCEMINUETTE_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceMinuette : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "*Dancing minuette*" << std::endl;
	}
};

#endif