#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CTriangleStrategy : public IShapeStrategy
{
public:
	CTriangleStrategy(Point vertex1, Point vertex2, Point vertex3)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{}

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};