#pragma once
#include "CShape.h"

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color)
		: CShape(color)
	{}

	void Draw(ICanvas& canvas) const;
	size_t GetVertexCount() const;
	double GetRadius() const;
	Point GetCenter() const;

private:
	size_t m_vertexCount = 0;
	double m_radius = 0;
	Point m_center;
};