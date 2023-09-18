#pragma once
#include <map>
#include <iostream>
#include "ICanvas.h"
#include "CShape.h"
#include "CShapeParams.h"

class CPicture
{
public:
	void AddShape(std::string const& id, CColor color, std::string const& shapeType, CShapeParams params);
	void MoveShape(std::string const& id, Point vector);
	void MovePicture(Point vector);
	void DeleteShape(std::string const& id);
	void ListShapes(std::ostream& stream);
	void ChangeColor(std::string const& id, CColor color);
	void ChangeShape(std::string const& id, std::string const& shape, CShapeParams params);
	void DrawShape(gfx::ICanvas& canvas, std::string const& id);
	void DrawPicture(gfx::ICanvas& canvas);

private:
	std::shared_ptr<CShape> GetShapeById(std::string const& id);

	std::map<std::string, CShape> m_shapes;
};