#pragma once
#include "IShapeStrategy.h"
#include "CShapeParams.h"

class CTriangleStrategy : public IShapeStrategy
{
public:
	CTriangleStrategy(CShapeParams const& params);

	void Draw(gfx::ICanvas& canvas, CColor const& color) override;
	void Move(Point vector) override;
	CShapeParams GetParams() const override;

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};