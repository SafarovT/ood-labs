#include <stdexcept>
#include "common.h"
#include "CLineStrategy.h"

void CLineStrategy::Draw(gfx::ICanvas& canvas, gfx::CColor const& color)
{
	canvas.SetColor(color);
	canvas.MoveTo(m_start);
	canvas.LineTo(m_end);
}

void CLineStrategy::Move(double dx, double dy)
{
	m_start.x += dx;
	m_start.y += dy;
	m_end.x += dx;
	m_end.y += dy;
}

std::string CLineStrategy::ToStr() const
{
	return "line "
		+ std::to_string(m_start.x) + " "
		+ std::to_string(m_start.y) + " "
		+ std::to_string(m_end.x) + " "
		+ std::to_string(m_end.y);
}