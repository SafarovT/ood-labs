#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, Point center, double verticalRadius, double horizontalRadius)
		: CShape(color)
		, m_center(center)
		, m_verticalRadius(verticalRadius),
		, m_horizontalRadius(horizontalRadius)
	{}

	void Draw(ICanvas& canvas) const;
	Point GetCenter() const;
	double GetVerticalRadius() const;
	double GetHorizontalRadius() const;

private:
	Point m_center;
	double m_horizontalRadius = 0;
	double m_verticalRadius = 0;
};