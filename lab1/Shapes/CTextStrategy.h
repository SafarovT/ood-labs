#pragma once
#include <vector>
#include "IShapeStrategy.h"

class CTextStrategy : public IShapeStrategy
{
public:
	CTextStrategy(Point leftTop, double fontSize, std::string const& text)
		: m_leftTop(leftTop)
		, m_fontSize(fontSize)
		, m_text(text)
	{}

	void Draw(gfx::ICanvas& canvas, gfx::CColor const& color) override;
	void Move(double dx, double dy) override;
	std::string ToStr() const override;

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};