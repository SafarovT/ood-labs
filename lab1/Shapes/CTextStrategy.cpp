#include <stdexcept>
#include "common.h"
#include "CTextStrategy.h"

CTextStrategy::CTextStrategy(std::vector<std::string> const& params)
{
	if (params.size() < 4)
	{
		throw new std::invalid_argument("Invalid rectangle arguments, use: <leftTopX> <leftTopY> <width> <height>");
	}
	m_leftTop = {StringToDouble(params[0]), StringToDouble(params[1])};
	m_fontSize = StringToDouble(params[2]);
	m_text = params[3];
}

void CTextStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
{
	canvas.SetColor(color);
	canvas.DrawText(m_leftTop, m_fontSize, m_text);
}

void CTextStrategy::Move(double dx, double dy)
{
	m_leftTop.x += dx;
	m_leftTop.y += dy;
}

std::string CTextStrategy::ToStr() const
{
	return "text "
		+ std::to_string(m_leftTop.x) + " "
		+ std::to_string(m_leftTop.y) + " "
		+ std::to_string(m_fontSize) + " "
		+ m_text;
}