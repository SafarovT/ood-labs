#pragma once
#include "IShapeStrategy.h"
#include <vector>

class CCircleStrategy : public IShapeStrategy
{
public:
	CCircleStrategy(Point center, double radius)
		: m_center(center)
		, m_radius(radius)
	{
	}

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_center;
	double m_radius;
};