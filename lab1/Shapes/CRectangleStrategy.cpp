#include <stdexcept>
#include "CRectangleStrategy.h"

CRectangleStrategy::CRectangleStrategy(CShapeParams const& params)
{
	std::vector<double> rectangleParams = params.GetParams();
	if (rectangleParams.size() < 4)
	{
		throw new std::invalid_argument("Invalid rectangle arguments, use: <leftTopX> <leftTopY> <width> <height>");
	}
	m_leftTop = { rectangleParams[0], rectangleParams[1] };
	m_width = rectangleParams[2];
	m_height = rectangleParams[3];
}

void CRectangleStrategy::Draw(gfx::ICanvas& canvas, CColor const& color)
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

void CRectangleStrategy::Move(Point vector)
{
	m_leftTop.x += vector.x;
	m_leftTop.y += vector.y;
}

CShapeParams CRectangleStrategy::GetParams() const
{
	return CShapeParams({ m_leftTop.x, m_leftTop.y, m_width, m_height });
}