#pragma once
#include "IShape.h"

class CEllipse : public IShape
{
public:
	CEllipse(Color color, Point center, double verticalRadius, double horizontalRadius)
		: m_color(color)
		, m_center(center)
		, m_verticalRadius(verticalRadius)
		, m_horizontalRadius(horizontalRadius)
	{}

	void Draw(ICanvas& canvas) const override
	{
		canvas.SetColor(GetColor());
		Point leftTop;
		leftTop.x = m_center.x - m_horizontalRadius;
		leftTop.y = m_center.y - m_verticalRadius;
		canvas.DrawEllipse(leftTop, m_horizontalRadius * 2, m_verticalRadius * 2);
	}

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

	Color GetColor() const override
	{
		return m_color;
	}

private:
	Color m_color;
	Point m_center;
	double m_horizontalRadius = 0;
	double m_verticalRadius = 0;
};