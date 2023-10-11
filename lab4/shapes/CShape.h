#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{}

	void Draw(ICanvas& canvas) const
	{
		canvas.SetColor(GetColor());
		DrawLayout(canvas);
	}

	Color GetColor() const
	{
		return m_color;
	}

private:
	virtual void DrawLayout(ICanvas& canvas) const = 0;
	Color m_color;
};