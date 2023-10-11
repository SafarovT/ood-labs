#pragma once
#include <string>
#include <memory>
#include "CShape.h"

class IShapeFactory
{
public:
	virtual std::shared_ptr<CShape> CreateShape(std::string const& description) = 0;
};