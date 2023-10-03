#include <stdexcept>
#include "common.h"
#include "CTextStrategy.h"

void CTextStrategy::Draw(gfx::ICanvas& canvas, gfx::CColor const& color)
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