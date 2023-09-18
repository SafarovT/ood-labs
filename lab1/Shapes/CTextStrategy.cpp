#include <stdexcept>
#include "CTextStrategy.h"

CTextStrategy::CTextStrategy(CShapeParams const& params)
{
	std::vector<double> textRectangleParams = params.GetParams();
	if (textRectangleParams.size() < 3)
	{
		throw new std::invalid_argument("Invalid rectangle arguments, use: <leftTopX> <leftTopY> <width> <height>");
	}
	m_leftTop = { textRectangleParams[0], textRectangleParams[1] };
	m_fontSize = textRectangleParams[2];
	m_text = params.GetText();
}

void CTextStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
{
	canvas.SetColor(color);
	canvas.DrawText(m_leftTop, m_fontSize, m_text);
}

void CTextStrategy::Move(Point vector)
{
	m_leftTop.x += vector.x;
	m_leftTop.y += vector.y;
}

CShapeParams CTextStrategy::GetParams() const
{
	return CShapeParams({ m_leftTop.x, m_leftTop.y, m_fontSize }, std::string(m_text));
}