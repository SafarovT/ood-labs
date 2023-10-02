#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point vertex1, Point vertex2, Point vertex3)
		: CShape(color)
		, m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{}
		
	void Draw(ICanvas& canvas) const;
	Point GetVertex1() const;
	Point GetVertex2() const;
	Point GetVertex3() const;

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};