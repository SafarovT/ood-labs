#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point m_leftTop, Point m_rightBottom)
		: CShape(color)
		, m_leftTop(m_leftTop)
		, m_rightBottom(m_rightBottom)
	{}

	void Draw(ICanvas& canvas)
	{
		canvas.SetColor(GetColor());
		Point vertex1 = m_leftTop;
		Point vertex2 = { m_leftTop.x, m_rightBottom.y };
		Point vertex3 = m_rightBottom;
		Point vertex4 = { m_rightBottom.x, m_leftTop.y };

		canvas.DrawLine(vertex1, vertex2);
		canvas.DrawLine(vertex2, vertex3);
		canvas.DrawLine(vertex3, vertex4);
		canvas.DrawLine(vertex4, vertex1);
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};