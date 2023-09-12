#ifndef DANCESTAYSTILL_H
#define DANCESTAYSTILL_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceStayStill : public IDanceBehavior
{
public:
	void Dance() const override {}
};

#endif