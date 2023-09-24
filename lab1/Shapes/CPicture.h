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
	// void MoveShape(std::string const& id, double dx, double dy);
	void MovePicture(double dx, double dy);
	void DeleteShape(std::string const& id);
	void ListShapes(std::ostream& stream);
	// void ChangeColor(std::string const& id, CColor color);
	// void ChangeShape(std::string const& id, std::string const& shape, std::vector<std::string> const& params);
	// void DrawShape(gfx::ICanvas& canvas, std::string const& id);
	void DrawPicture(gfx::ICanvas& canvas);

private:
	std::map<std::string, std::shared_ptr<CShape>> m_shapesIds;
	std::vector<std::shared_ptr<CShape>> m_shapes;
};