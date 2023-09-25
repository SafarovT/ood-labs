#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "ICanvas.h"
#include "CShape.h"

class CPicture
{
public:
	std::shared_ptr<CShape> GetShapeById(std::string const& id);

	void AddShape(std::string const& id, CColor color, std::string const& shapeType, std::vector<std::string> const& params);
	void MovePicture(double dx, double dy);
	void DeleteShape(std::string const& id);
	void ListShapes(std::ostream& stream);
	void DrawPicture(gfx::ICanvas& canvas);

private:
	std::map<std::string, std::shared_ptr<CShape>> m_shapesIds;
	std::vector<std::shared_ptr<CShape>> m_shapes;
};