#include <stdexcept>
#include "common.h"
#include "CLineStrategy.h"

CLineStrategy::CLineStrategy(std::vector<std::string> const& params)
{
	if (params.size() < 4)
	{
		throw new std::invalid_argument("Invalid line arguments, use: <x1> <y1> <x2> <y2>");
	}
	m_start = { StringToDouble(params[0]), StringToDouble(params[1])};
	m_end = { StringToDouble(params[2]), StringToDouble(params[3]) };
}

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