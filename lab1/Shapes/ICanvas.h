#pragma once
#include <string>
#include "Point.h"
#include "CColor.h"

namespace gfx
{
	class ICanvas
	{
	public:
		virtual ~ICanvas() {};

		virtual void MoveTo(Point point) = 0;
		virtual void SetColor(gfx::CColor color) = 0;
		virtual void LineTo(Point point) = 0;
		virtual void DrawEllipse(Point leftTopPoint, Point rightBottomPoint) = 0;
		virtual void DrawText(Point leftTopPoint, double fontSize, std::string const& text) = 0;
	};
}