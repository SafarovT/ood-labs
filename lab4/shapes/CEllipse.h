#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(Color color, Point center, double verticalRadius, double horizontalRadius)
		: CShape(color)
		, m_center(center)
		, m_verticalRadius(verticalRadius)
		, m_horizontalRadius(horizontalRadius)
	{}

	Point GetCenter() const
	{
		return m_center;
	}

	double GetVerticalRadius() const
	{
		return m_verticalRadius;
	}

	double GetHorizontalRadius() const
	{
		return m_horizontalRadius;
	}

private:
	Point m_center;
	double m_horizontalRadius = 0;
	double m_verticalRadius = 0;

	void DrawLayout(ICanvas& canvas) const override
	{
		Point leftTop;
		leftTop.x = m_center.x - m_horizontalRadius;
		leftTop.y = m_center.y - m_verticalRadius;
		canvas.DrawEllipse(leftTop, m_horizontalRadius * 2, m_verticalRadius * 2);
	}
};