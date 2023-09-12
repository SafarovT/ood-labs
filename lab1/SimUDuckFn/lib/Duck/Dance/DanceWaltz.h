#ifndef DANCEWALTZ_H
#define DANCEWALTZ_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "*Dancing waltz*" << std::endl;
	}
};

#endif