#pragma once
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() {};

	virtual void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) = 0;
	virtual void Move(double dx, double dy) = 0;
	virtual std::string ToStr() const = 0;
};