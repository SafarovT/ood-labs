#include <stdexcept>
#include "common.h"
#include "CCircleStrategy.h"

void CCircleStrategy::Draw(gfx::ICanvas& canvas, gfx::CColor const& color)
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