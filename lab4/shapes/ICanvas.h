#pragma once
#include "Point.h"
#include "Color.h"

class ICanvas
{
public:
	~ICanvas() {};

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point fromPoint, Point toPoint) = 0;
	virtual void DrawEllipse(Point leftTop, double width, double left) = 0;
};