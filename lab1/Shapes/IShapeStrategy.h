#pragma once
#include "ICanvas.h"
#include "CShapeParams.h"

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() {};

	virtual void Draw(gfx::ICanvas& canvas, CColor const& color) = 0;
	virtual void Move(Point vector) = 0;
	virtual CShapeParams GetParams() const = 0;
};