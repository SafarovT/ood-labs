#include <stdexcept>
#include "CTriangleStrategy.h"

CTriangleStrategy::CTriangleStrategy(CShapeParams const& params)
{
	std::vector<double> triangleParams = params.GetParams();
	if (triangleParams.size() < 6)
	{
		throw new std::invalid_argument("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
	}
	m_vertex1 = { triangleParams[0], triangleParams[1] };
	m_vertex2 = { triangleParams[2], triangleParams[3] };
	m_vertex3 = { triangleParams[4], triangleParams[5] };
}

void CTriangleStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
{
	canvas.SetColor(color);
	canvas.MoveTo(m_vertex1);
	canvas.LineTo(m_vertex2);
	canvas.LineTo(m_vertex3);
	canvas.LineTo(m_vertex1);
}

void CTriangleStrategy::Move(Point vector)
{
	m_vertex1 = { m_vertex1.x + vector.x, m_vertex1.y + vector.y };
	m_vertex2 = { m_vertex2.x + vector.x, m_vertex2.y + vector.y };
	m_vertex3 = { m_vertex3.x + vector.x, m_vertex3.y + vector.y };
}

CShapeParams CTriangleStrategy::GetParams() const
{
	return CShapeParams({ m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y });
}