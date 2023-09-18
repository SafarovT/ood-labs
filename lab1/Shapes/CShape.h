#pragma once
#include <memory>
#include "ICanvas.h"
#include "IShapeStrategy.h"
#include "CShapeParams.h"
#include <cassert>

class CShape
{
public:
	CShape(CColor color, std::unique_ptr<IShapeStrategy> shapeStrategy)
		: m_shapeStrategy(std::move(shapeStrategy))
		, m_color(color)
	{
		assert(m_shapeStrategy);
	}

	CColor GetColor() const;
	void Draw(gfx::ICanvas& canvas);
	void Move(Point vector);
	void SetColor(CColor color);
	CShapeParams GetShapeParams();
	void SetShapeStrategy(std::unique_ptr<IShapeStrategy> shapeStrategy);

private:
	CColor m_color;
	std::unique_ptr<IShapeStrategy> m_shapeStrategy;
};