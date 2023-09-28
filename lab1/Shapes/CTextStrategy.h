#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CTextStrategy : public IShapeStrategy
{
public:
	CTextStrategy(std::vector<std::string> const& params);

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};