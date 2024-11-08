#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	void SetColor(Color color) override
	{
		m_color = color;
	}

	void DrawLine(Point fromPoint, Point toPoint) override
	{
		std::string line =
			"<line x1=\"" + std::to_string(fromPoint.x) + "\" "
			+ "y1=\"" + std::to_string(fromPoint.y) + "\" "
			+ "x2=\"" + std::to_string(toPoint.x) + "\" "
			+ "y2=\"" + std::to_string(toPoint.y) + "\" "
			+ "style=\"stroke:" + ColorToStr(m_color)
			+ ";stroke-width:3" + "\" />";

		m_svgCode << line << std::endl;
	}

	void DrawEllipse(Point leftTop, double width, double height) override
	{
		std::string ellipse =
			"<ellipse cx=\"" + std::to_string(leftTop.x + width / 2) + "\" "
			+ "cy=\"" + std::to_string(leftTop.y + height / 2) + "\" "
			+ "rx=\"" + std::to_string(width / 2) + "\" "
			+ "ry=\"" + std::to_string(height / 2) + "\" "
			+ "style=\"stroke:" + ColorToStr(m_color)
			+ ";stroke-width:3" + +"; fill:none;\" />";

		m_svgCode << ellipse << std::endl;
	}

	void Save(std::string const& outputFilePath = "image.svg") // сделат так чтобы в save можно было передать имя файла
	{
		std::ofstream output(outputFilePath);

		if (!output.good())
		{
			throw std::invalid_argument("Invalid file path");
		}

		output << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">" << std::endl
			<< m_svgCode.str() << std::endl
			<< "</svg>" << std::endl;
		output.close();
	}

private:
	Color m_color;
	std::stringstream m_svgCode = std::stringstream("");
};