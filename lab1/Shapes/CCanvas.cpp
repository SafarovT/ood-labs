#include "CCanvas.h"
#include "common.h"
#include <fstream>

void CCanvas::MoveTo(Point point)
{
	m_position = point;
}

void CCanvas::SetColor(CColor color)
{
	m_color = color;
}

void CCanvas::Save()
{
	std::ofstream output(m_outputFilePath);

	if (!output.good())
	{
		throw std::invalid_argument("Invalid file path");
	}

	output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl
		<< m_svgCode.str() << std::endl
		<< "</svg>" << std::endl;
	output.close();
}

void CCanvas::LineTo(Point point)
{
	std::string line =
		"<line x1=\"" + std::to_string(m_position.x) + "\" "
		+ "y1=\"" + std::to_string(m_position.y) + "\" "
		+ "x2=\"" + std::to_string(point.x) + "\" "
		+ "y2=\"" + std::to_string(point.y) + "\" "
		+ "style=\"stroke:#" + m_color.GetColor()
		+ ";stroke-width:1" + "\" />";

	m_svgCode << line << std::endl;
}

void CCanvas::DrawEllipse(Point leftTopPoint, Point rightBottomPoint)
{
	std::string ellipse =
		"<ellipse cx=\"" + std::to_string((leftTopPoint.x + rightBottomPoint.x) / 2) + "\" "
		+ "cy=\"" + std::to_string((leftTopPoint.y + rightBottomPoint.y) / 2) + "\" "
		+ "rx=\"" + std::to_string((rightBottomPoint.x - leftTopPoint.x) / 2) + "\" "
		+ "ry=\"" + std::to_string((rightBottomPoint.y - leftTopPoint.y) / 2) + "\" "
		+ "style=\"stroke:#" + m_color.GetColor()
		+ ";stroke-width:1" +  + "; fill:none;\" />";

	m_svgCode << ellipse << std::endl;
}

void CCanvas::DrawText(Point leftTopPoint, double fontSize, std::string const& text)
{
	std::string svgText =
		"<text x=\"" + std::to_string(leftTopPoint.x) + "\" "
		+ "y=\"" + std::to_string(leftTopPoint.y) + "\" "
		+ "font-size=\"" + std::to_string(fontSize) + "\" "
		+ "fill=\"#" + m_color.GetColor() + "\">"
		+ text + "</text>";

	m_svgCode << svgText << std::endl;
}