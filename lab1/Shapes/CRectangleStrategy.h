#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CRectangleStrategy : public IShapeStrategy
{
public:
	CRectangleStrategy(Point leftTop, double width, double height)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{}

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_leftTop;
	double m_width, m_height;
};