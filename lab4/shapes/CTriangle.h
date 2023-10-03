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
		
	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex1, m_vertex3);
	}

	Point GetVertex1() const
	{
		return m_vertex1;
	}

	Point GetVertex2() const
	{
		return m_vertex2;
	}

	Point GetVertex3() const
	{
		return m_vertex3;
	}


private:
	Point m_vertex1, m_vertex2, m_vertex3;
};