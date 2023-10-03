#pragma once
#include "Color.h"
#include "ICanvas.h"

class IShape
{
public:
	virtual void Draw(ICanvas& canvas) const = 0;
	virtual Color GetColor() const = 0;
};