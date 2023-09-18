#pragma once
#include "IShapeStrategy.h"
#include "CShapeParams.h"

class CCircleStrategy : public IShapeStrategy
{
public:
	CCircleStrategy(CShapeParams const& params);
	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(Point vector) override;
	CShapeParams GetParams() const override;

private:
	Point m_center;
	double m_radius;
};