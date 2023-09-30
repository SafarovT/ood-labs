#include "CPicture.h"
#include "CShapeStrategyFactory.h"
#include <algorithm>

using namespace shapes;

void CPicture::AddShape(std::string const& id, gfx::CColor color, std::string const& shapeType, std::vector<std::string> const& params)
{
	auto foundPicture = GetShapeById(id);
	if (foundPicture != nullptr)
	{
		throw std::logic_error("Figure with this id already exists");
	}
	std::unique_ptr<IShapeStrategy> shapeStrategy = CShapeStrategyFactory::CreateShapeStrategy(shapeType, params);
	auto newShape = std::make_shared<CShape>(color, std::move(shapeStrategy));
	m_shapes.push_back(newShape);
	// добавлять в shapes
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
	m_shapesIds.erase(id); 
	// удалять из вектора быстрее чем за O(n)
}

void CPicture::ListShapes(std::ostream& stream)
{
	size_t number = 1;
	for (auto& shape : m_shapes)
	{
		stream << shape->ToStr() << std::endl;
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