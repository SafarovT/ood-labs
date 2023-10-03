#pragma once
#include <vector>
#include <memory>
#include "CShape.h"

class CPictureDraft
{
public:
	CPictureDraft()
		: m_shapes({})
	{}

	void AddShape(std::shared_ptr<CShape> shape)
	{
		m_shapes.push_back(shape);
	}

	std::shared_ptr<CShape> GetShape(size_t index) const
	{
		if (index >= GetShapesCount())
		{
			return nullptr;
		}

		return m_shapes[index];
	}

	size_t GetShapesCount() const
	{
		return m_shapes.size();
	}

private:
	std::vector<std::shared_ptr<CShape>> m_shapes;
};