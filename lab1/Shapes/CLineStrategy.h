#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CLineStrategy : public IShapeStrategy
{
public:
	CLineStrategy(Point start, Point end)
		: m_start(start)
		, m_end(end)
	{}

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_start, m_end;
};