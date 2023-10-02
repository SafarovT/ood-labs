#pragma once
#include "ICanvas.h"

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(Color color)
		: m_color(color)
	{}

	void SetColor(Color color) override;
	void DrawLine(Point fromPoint, Point toPoint) override;
	void DrawEllipse(Point leftTop, double width, double left) override;
	void Save() const;
private:
	Color m_color;
};