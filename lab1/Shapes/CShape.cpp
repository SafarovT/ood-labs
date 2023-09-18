#include "CShape.h"

CColor CShape::GetColor() const
{
	return m_color;
}

void CShape::Draw(gfx::ICanvas& canvas)
{
	m_shapeStrategy->Draw(canvas, this->GetColor());
}

void CShape::Move(Point vector)
{
	m_shapeStrategy->Move(vector);
}

CShapeParams CShape::GetShapeParams()
{
	return m_shapeStrategy->GetParams();
}

void CShape::SetColor(CColor color)
{
	m_color = color;
}

void CShape::SetShapeStrategy(std::unique_ptr<IShapeStrategy> shapeStrategy)
{
	m_shapeStrategy = std::move(shapeStrategy);
}