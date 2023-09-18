#pragma once
#include "IShapeStrategy.h"
#include "CShapeParams.h"

class CLineStrategy : public IShapeStrategy
{
public:
	CLineStrategy(CShapeParams const& params);

	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(Point vector) override;
	CShapeParams GetParams() const override;

private:
	Point m_start, m_end;
};