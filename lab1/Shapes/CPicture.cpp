#include "CPicture.h"
#include "CShapeStrategyFactory.h"
#include <algorithm>

void CPicture::AddShape(std::string const& id, CColor color, std::string const& shapeType, CShapeParams params)
{
	auto foundPicture = GetShapeById(id);
	if (foundPicture != nullptr)
	{
		throw std::logic_error("Figure with this id already exists");
	}
	std::unique_ptr<IShapeStrategy> shapeStrategy = CShapeStrategyFactory::CreateShapeStrategy(shapeType, params);
	m_shapes.insert({ id, CShape(color, std::move(shapeStrategy)) });
}

void CPicture::MoveShape(std::string const& id, double dx, double dy)
{
	auto shape = GetShapeById(id);
	if (shape != nullptr)
	{
		shape->Move(dx, dy);
	}
}

void CPicture::MovePicture(double dx, double dy)
{
	for (auto& idShapePair : m_shapes)
	{
		idShapePair.second.Move(dx, dy);
	}
}

void CPicture::DeleteShape(std::string const& id)
{
	m_shapes.erase(id);
}

void CPicture::ListShapes(std::ostream& stream)
{
	size_t number = 1;
	for (auto& idShapePair : m_shapes)
	{
		stream << std::to_string(number) << " "
			<< idShapePair.second.GetShapeType() << " "
			<< idShapePair.first << " " << idShapePair.second.GetColor().GetColor() << " "
			<< idShapePair.second.GetShapeParams().GetParamsStr() << std::endl;
		number++;
	}
}

void CPicture::ChangeColor(std::string const& id, CColor color)
{
	auto shape = GetShapeById(id);
	if (shape != nullptr)
	{
		shape->SetColor(color);
	}
}

void CPicture::ChangeShape(std::string const& id, std::string const& shapeType, CShapeParams params)
{
	auto shape = GetShapeById(id);
	std::unique_ptr<IShapeStrategy> shapeStrategy = CShapeStrategyFactory::CreateShapeStrategy(shapeType, params);
	if (shapeStrategy != nullptr)
	{
		shape->SetShapeStrategy(std::move(shapeStrategy));
	}
}

void CPicture::DrawShape(gfx::ICanvas& canvas, std::string const& id)
{
	auto shape = GetShapeById(id);
	if (shape != nullptr)
	{
		shape->Draw(canvas);
	}
}

void CPicture::DrawPicture(gfx::ICanvas& canvas)
{
	for (auto& idShapePair : m_shapes)
	{
		idShapePair.second.Draw(canvas);
	}
}

CShape* CPicture::GetShapeById(std::string const& id)
{
	auto idShapePair = m_shapes.find(id);
	if (idShapePair == m_shapes.end())
	{
		return nullptr;
	}

	return &(idShapePair->second);
}