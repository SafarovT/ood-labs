#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{}

	void Draw(ICanvas& canvas);
	Color GetColor() const;

private:
	Color m_color;
};