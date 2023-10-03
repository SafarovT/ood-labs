#pragma once
#include <iostream>
#include <stdexcept>
#include "common.h"
#include "IShapeFactory.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CRegularPolygon.h"

class CShapeFactory : public IShapeFactory
{
public:
	std::shared_ptr<IShape> CreateShape(std::string const& description) override
	{
		Params params = ParseParams(description);
		if (params.size() < 2)
		{
			throw new std::exception("Empty shape description");
		}
		Color color = StrToColor(params[0]);
		params.pop_front();
		std::string shape = params[0];
		params.pop_front();
		std::shared_ptr<IShape> shapePtr = nullptr;
		if (shape == "rectangle")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid rectangle arguments, use: rectangle <leftTopX> <leftTopY> <rightBottomX> <rightBottomY>");
			}
			Point leftTop = { StringToDouble(params[0]), StringToDouble(params[1]) };
			Point rightBottom = { StringToDouble(params[2]), StringToDouble(params[3]) };
			shapePtr = std::make_shared<IShape>(CRectangle(color, leftTop, rightBottom));
		}
		else if (shape == "triangle")
		{
			if (params.size() < 6)
			{
				throw new std::invalid_argument("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
			}
			Point vertex1 = { StringToDouble(params[0]), StringToDouble(params[1]) };
			Point vertex2 = { StringToDouble(params[2]), StringToDouble(params[3]) };
			Point vertex3 = { StringToDouble(params[4]), StringToDouble(params[5]) };

			shapePtr = std::make_shared<IShape>(CTriangle(color, vertex1, vertex2, vertex3));
		}
		else if (shape == "ellipse")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid ellipse arguments, use: ellipse <centerX> <centerY> <verticalRadius> <horizontalRadius>");
			}
			Point center = { StringToDouble(params[0]), StringToDouble(params[1]) };
			double verticalRadius = StringToDouble(params[2]);
			double horizontalRadius = StringToDouble(params[3]);
			
			shapePtr = std::make_shared<IShape>(CEllipse(color, center, verticalRadius, horizontalRadius));
		}
		else if (shape == "polygon")
		{
			if (params.size() < 4)
			{
				throw new std::invalid_argument("Invalid polygon arguments, use: ellipse <centerX> <centerY> <vertexCount> <radius>");
			}
			Point center = { StringToDouble(params[0]), StringToDouble(params[1]) };
			size_t vertexCount = static_cast<size_t>(StringToDouble(params[2]));
			double radius = StringToDouble(params[3]);

			shapePtr = std::make_shared<IShape>(CRegularPolygon(color, center, vertexCount, radius));
		}

		return shapePtr;
	}

private:
	using Params = std::deque<std::string>;

	Params ParseParams(std::string const& description)
	{
		std::string paramsString = Trim(description);

		return Explode(paramsString, ' ');
	}
};