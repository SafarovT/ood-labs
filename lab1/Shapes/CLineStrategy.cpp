#include <stdexcept>
#include "CLineStrategy.h"

CLineStrategy::CLineStrategy(CShapeParams const& params)
{
	std::vector<double> lineParams = params.GetParams();
	if (lineParams.size() < 4)
	{
		throw new std::invalid_argument("Invalid line arguments, use: <x1> <y1> <x2> <y2>");
	}
	m_start = { lineParams[0], lineParams[1] };
	m_end = { lineParams[2], lineParams[3] };
}

void CLineStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
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

CShapeParams CLineStrategy::GetParams() const
{
	return CShapeParams({ m_start.x, m_start.y, m_end.x, m_end.y });
}

std::string CLineStrategy::GetName() const
{
	return "line";
}