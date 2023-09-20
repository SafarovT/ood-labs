#include <stdexcept>
#include "CCircleStrategy.h"

CCircleStrategy::CCircleStrategy(CShapeParams const& params)
{
	std::vector<double> circleParams = params.GetParams();
	if (circleParams.size() < 3)
	{
		throw new std::invalid_argument("Invalid circle arguments, use: <centerX> <centerY> <radius>");
	}
	m_center = { circleParams[0], circleParams[1] };
	m_radius = circleParams[2];
}

void CCircleStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
{
	canvas.SetColor(color);
	Point leftTopPoint = { m_center.x - m_radius, m_center.y - m_radius };
	Point rightBottomPoint = { m_center.x + m_radius, m_center.y + m_radius };
	canvas.DrawEllipse(leftTopPoint, rightBottomPoint);
}

void CCircleStrategy::Move(double dx, double dy)
{
	m_center.x += dx;
	m_center.y += dy;
}

CShapeParams CCircleStrategy::GetParams() const
{
	return CShapeParams({ m_center.x, m_center.y, m_radius });
}

std::string CCircleStrategy::GetName() const
{
	return "circle";
}