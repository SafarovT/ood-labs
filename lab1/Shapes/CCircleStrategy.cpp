#include <stdexcept>
#include "common.h"
#include "CCircleStrategy.h"

CCircleStrategy::CCircleStrategy(std::vector<std::string> const& params)
{
	if (params.size() < 3)
	{
		throw new std::invalid_argument("Invalid circle arguments, use: <centerX> <centerY> <radius>");
	}
	m_center = { StringToDouble(params[0]), StringToDouble(params[1])};
	m_radius = StringToDouble(params[3]);
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

std::string CCircleStrategy::ToStr() const
{
	return "circle "
		+ std::to_string(m_center.x) + " "
		+ std::to_string(m_center.y) + " "
		+ std::to_string(m_radius);
}