#pragma once
#include <vector>
#include <memory>
#include "CShape.h"

class CPictureDraft
{
public:
	CPictureDraft(std::vector<std::unique_ptr<CShape>>&& shapes)
		: m_shapes(shapes)
	{}

	double GetShapesCount() const;
	CShape GetShape(size_t index) const;

private:
	std::vector<std::unique_ptr<CShape>> m_shapes;
};