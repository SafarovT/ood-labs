#include <stdexcept>
#include "common.h"
#include "CRectangleStrategy.h"

CRectangleStrategy::CRectangleStrategy(std::vector<std::string> const& params)
{
	if (params.size() < 4)
	{
		throw new std::invalid_argument("Invalid rectangle arguments, use: <leftTopX> <leftTopY> <width> <height>");
	}
	m_leftTop = { StringToDouble(params[0]), StringToDouble(params[1]) };
	m_width = StringToDouble(params[2]);
	m_height = StringToDouble(params[3]);
}

void CRectangleStrategy::Draw(gfx::ICanvas& canvas, gfx::CColor const& color)
{
	canvas.SetColor(color);
	Point currentPoint = m_leftTop;
	canvas.MoveTo(currentPoint);
	currentPoint.x += m_width;
	canvas.LineTo(currentPoint);
	currentPoint.y += m_height;
	canvas.LineTo(currentPoint);
	currentPoint.x -= m_width;
	canvas.LineTo(currentPoint);
	currentPoint.y -= m_height;
	canvas.LineTo(currentPoint);
}

void CRectangleStrategy::Move(double dx, double dy)
{
	m_leftTop.x += dx;
	m_leftTop.y += dy;
}

std::string CRectangleStrategy::ToStr() const
{
	return "rectangle "
		+ std::to_string(m_leftTop.x) + " "
		+ std::to_string(m_leftTop.y) + " "
		+ std::to_string(m_width) + " "
		+ std::to_string(m_height);
}