#pragma once
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() = default;

	virtual void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) = 0; // const
	virtual void Move(double dx, double dy) = 0;
	virtual std::string ToStr() const = 0;
};