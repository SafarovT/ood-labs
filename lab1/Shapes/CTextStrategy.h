#pragma once
#include "IShapeStrategy.h"
#include "CShapeParams.h"

class CTextStrategy : public IShapeStrategy
{
public:
	CTextStrategy(CShapeParams const& params);

	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(double dx, double dy) override;
	CShapeParams GetParams() const override;
	std::string GetName() const override;

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};