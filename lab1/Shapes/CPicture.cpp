#include "CPicture.h"
#include <algorithm>

using namespace shapes;

void CPicture::AddShape(std::string const& id, gfx::CColor color, std::unique_ptr<IShapeStrategy> shapeStrategy)
{
	auto foundPicture = GetShapeById(id);
	if (foundPicture != nullptr)
	{
		throw std::logic_error("Figure with this id already exists");
	}
	auto newShapePtr = std::make_shared<CShape>(CShape(id, color, std::move(shapeStrategy)));
	m_shapes.push_back(newShapePtr);
	m_shapesIds.emplace(id, newShapePtr);
}

void CPicture::MovePicture(double dx, double dy)
{
	for (auto& idShapePair : m_shapesIds)
	{
		idShapePair.second->Move(dx, dy);
	}
}

void CPicture::DeleteShape(std::string const& id)
{
	auto shapePtr = GetShapeById(id);
	std::erase(m_shapes, shapePtr);
	m_shapesIds.erase(id); 
}

void CPicture::ListShapes(std::ostream& stream)
{
	size_t number = 1;
	for (auto& shape : m_shapes)
	{
		stream << number << shape->ToStr() << std::endl;
		number++;
	}
}

void CPicture::DrawPicture(gfx::ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

std::shared_ptr<CShape> CPicture::GetShapeById(std::string const& id)
{
	auto idShapePair = m_shapesIds.find(id);
	if (idShapePair == m_shapesIds.end())
	{
		return nullptr;
	}

	return idShapePair->second;
}