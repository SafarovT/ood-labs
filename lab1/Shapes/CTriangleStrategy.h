#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CTriangleStrategy : public IShapeStrategy
{
public:
	CTriangleStrategy(std::vector<std::string> const& params);

	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};