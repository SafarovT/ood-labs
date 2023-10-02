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

	void Draw(ICanvas& canvas);
	Point GetLeftTop() const;
	Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};