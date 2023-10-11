#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "CShape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, Point center, size_t vertexCount, double radius)
		: CShape(color)
		, m_center(center)
		, m_vertexCount(vertexCount)
		, m_radius(radius)
	{}

	size_t GetVertexCount() const
	{
		return m_vertexCount;
	}

	double GetRadius() const
	{
		return m_radius;
	}

	Point GetCenter() const
	{
		return m_center;
	}

private:
	Point m_center;
	size_t m_vertexCount = 0;
	double m_radius = 0;

	void DrawLayout(ICanvas& canvas) const override
	{
		Point start = { m_center.x + m_radius, m_center.y };
		Point end;

		for (size_t i = 1; i <= m_vertexCount; i++)
		{
			end.x = m_center.x + (m_radius * cos(2 * M_PI * i / m_vertexCount));
			end.y = m_center.y + (m_radius * sin(2 * M_PI * i / m_vertexCount));

			canvas.DrawLine(start, end);
			start = end;
		}
	}
};