#pragma once
#include <sstream>
#include "ICanvas.h"

class CCanvas : public gfx::ICanvas
{
public:
	CCanvas(std::string&& outputFilePath)
		: m_outputFilePath(std::move(outputFilePath))
		, m_color(CColor(0))
		, m_position({ 0, 0 })
	{
		m_svgCode = std::stringstream("");
	}

	void MoveTo(Point point) override;
	void SetColor(CColor color) override;
	void LineTo(Point point) override;
	void DrawEllipse(Point leftTopPoint, Point rightBottomPoint) override;
	void DrawText(Point leftTopPoint, double fontSize, std::string const& text) override;
	void Save();

private:
	CColor m_color;
	Point m_position;
	std::string m_outputFilePath;
	std::stringstream m_svgCode;
};