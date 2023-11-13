#pragma once
#include <vector>
#include "Point.h"
#include "CRGBAColor.h"

class ICanvas
{
public:
	virtual void DrawLine(Point start, Point end) = 0;
	virtual void DrawEllipse(Point center, double xRadius, double yRadius) = 0;
	virtual void FillEllipse(Point center, double xRadius, double yRadius) = 0;
	virtual void FillPolygon(std::vector<Point> points) = 0;
	virtual void SetFillColor(CRGBAColor color) = 0;
	virtual void SetLineColor(CRGBAColor color) = 0;
	virtual void SetLineThickness(double thickness) = 0;
};