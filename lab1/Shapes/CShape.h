#pragma once
#include <memory>
#include "ICanvas.h"
#include "IShapeStrategy.h"
#include <cassert>

namespace shapes
{
	class CShape
	{
	public:
		CShape(gfx::CColor color, std::unique_ptr<IShapeStrategy>&& shapeStrategy)
			: m_shapeStrategy(std::move(shapeStrategy))
			, m_color(color)
		{
			assert(m_shapeStrategy);
		}

		void Draw(gfx::ICanvas& canvas);
		void Move(double dx, double dy);
		void SetColor(gfx::CColor color);
		std::string ToStr() const;
		void SetShapeStrategy(std::unique_ptr<IShapeStrategy> shapeStrategy);

	private:
		gfx::CColor m_color;
		std::unique_ptr<IShapeStrategy> m_shapeStrategy;
	};
}