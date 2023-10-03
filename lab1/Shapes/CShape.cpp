#include "CShape.h"

using namespace shapes;

std::string CShape::GetId() const
{
	return m_id;
}

void CShape::Draw(gfx::ICanvas& canvas) const
{
	m_shapeStrategy->Draw(canvas, m_color);
}

void CShape::Move(double dx, double dy)
{
	m_shapeStrategy->Move(dx, dy);
}

void CShape::SetColor(gfx::CColor color)
{
	m_color = color;
}

void CShape::SetShapeStrategy(std::unique_ptr<IShapeStrategy> shapeStrategy)
{
	m_shapeStrategy = std::move(shapeStrategy);
}

std::string CShape::ToStr() const
{
	return m_id + " " + m_color.GetColor() + " " + m_shapeStrategy->ToStr();
}