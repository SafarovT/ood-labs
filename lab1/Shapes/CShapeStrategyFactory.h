#pragma once
#include <memory>
#include "IShapeStrategy.h"
#include "CTextStrategy.h"
#include "CLineStrategy.h"
#include "CRectangleStrategy.h"
#include "CCircleStrategy.h"
#include "CTriangleStrategy.h"

class CShapeStrategyFactory
{
public:
	static std::unique_ptr<IShapeStrategy> CreateShapeStrategy(const std::string& type, const std::vector<std::string> params)
	{
		std::unique_ptr<IShapeStrategy>	shape = nullptr;

		if (type == "text")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid text arguments, use: <leftTopX> <leftTopY> <fontSize> <text>");
			}
			Point leftTop = { StringToDouble(params[0]), StringToDouble(params[1]) };
			double fontSize = StringToDouble(params[2]);
			shape = std::make_unique<CTextStrategy>(leftTop, fontSize, params[3]);
		}
		else if (type == "line")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid line arguments, use: <x1> <y1> <x2> <y2>");
			}
			Point start = { StringToDouble(params[0]), StringToDouble(params[1]) };
			Point end = { StringToDouble(params[2]), StringToDouble(params[3]) };
			shape = std::make_unique<CLineStrategy>(start, end);
		}
		else if (type == "rectangle")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid rectangle arguments, use: <leftTopX> <leftTopY> <width> <height>");
			}
			Point leftTop = { StringToDouble(params[0]), StringToDouble(params[1]) };
			double width = StringToDouble(params[2]);
			double height = StringToDouble(params[3]);
			shape = std::make_unique<CRectangleStrategy>(leftTop, width, height);
		}
		else if (type == "circle")
		{
			if (params.size() < 3)
			{
				throw new std::invalid_argument("Invalid circle arguments, use: <centerX> <centerY> <radius>");
			}
			Point center = { StringToDouble(params[0]), StringToDouble(params[1]) };
			double radius = StringToDouble(params[3]);
			shape = std::make_unique<CCircleStrategy>(center, radius);
		}
		else if (type == "triangle")
		{
			if (params.size() < 6)
			{
				throw new std::invalid_argument("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
			}
			Point vertex1 = { StringToDouble(params[0]), StringToDouble(params[1]) };
			Point vertex2 = { StringToDouble(params[2]), StringToDouble(params[3]) };
			Point vertex3 = { StringToDouble(params[4]), StringToDouble(params[5]) };
			shape = std::make_unique<CTriangleStrategy>(vertex1, vertex2, vertex3);
		}

		return shape;
	}
};