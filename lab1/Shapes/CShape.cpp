#include "CShape.h"

void CShape::Draw(gfx::ICanvas& canvas)
{
	m_shapeStrategy->Draw(canvas, this->GetColor());
}

void CShape::Move(double dx, double dy)
{
	m_shapeStrategy->Move(dx, dy);
}

void CShape::SetColor(CColor color)
{
	m_color = color;
}

void CShape::SetShapeStrategy(std::unique_ptr<IShapeStrategy> shapeStrategy)
{
	m_shapeStrategy = std::move(shapeStrategy);
}

std::string CShape::ToStr() const
{
	return m_color.GetColor() + m_shapeStrategy->ToStr();
}