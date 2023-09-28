#include <stdexcept>
#include "common.h"
#include "CTriangleStrategy.h"

CTriangleStrategy::CTriangleStrategy(std::vector<std::string> const& params)
{
	if (params.size() < 6)
	{
		throw new std::invalid_argument("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
	}
	m_vertex1 = {StringToDouble(params[0]), StringToDouble(params[1])};
	m_vertex2 = {StringToDouble(params[2]), StringToDouble(params[3])};
	m_vertex3 = {StringToDouble(params[4]), StringToDouble(params[5])};
}

void CTriangleStrategy::Draw(gfx::ICanvas& canvas, gfx::CColor const& color)
{
	canvas.SetColor(color);
	canvas.MoveTo(m_vertex1);
	canvas.LineTo(m_vertex2);
	canvas.LineTo(m_vertex3);
	canvas.LineTo(m_vertex1);
}

void CTriangleStrategy::Move(double dx, double dy)
{
	m_vertex1 = { m_vertex1.x + dx, m_vertex1.y + dy };
	m_vertex2 = { m_vertex2.x + dx, m_vertex2.y + dy };
	m_vertex3 = { m_vertex3.x + dx, m_vertex3.y + dy };
}

std::string CTriangleStrategy::ToStr() const
{
	return "triangle "
		+ std::to_string(m_vertex1.x) + " "
		+ std::to_string(m_vertex1.y) + " "
		+ std::to_string(m_vertex2.x) + " "
		+ std::to_string(m_vertex2.y) + " "
		+ std::to_string(m_vertex3.x) + " "
		+ std::to_string(m_vertex3.y) + " ";
}