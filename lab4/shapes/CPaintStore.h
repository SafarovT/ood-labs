#pragma once
#include "Color.h"

class CPaintStore
{
public:
	int GetPaintCost(Color color, size_t amount) const
	{
		return amount;
	}
};