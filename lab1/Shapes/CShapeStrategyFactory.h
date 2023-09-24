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
			shape = std::make_unique<CTextStrategy>(params);
		}
		else if (type == "line")
		{
			shape = std::make_unique<CLineStrategy>(params);
		}
		else if (type == "rectangle")
		{
			shape = std::make_unique<CRectangleStrategy>(params);
		}
		else if (type == "circle")
		{
			shape = std::make_unique<CCircleStrategy>(params);
		}
		else if (type == "triangle")
		{
			shape = std::make_unique<CTriangleStrategy>(params);
		}

		return shape;
	}
};