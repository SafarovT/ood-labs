#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CRectangleStrategy : public IShapeStrategy
{
public:
	CRectangleStrategy(std::vector<std::string> const& params);

	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_leftTop;
	double m_width, m_height;
};