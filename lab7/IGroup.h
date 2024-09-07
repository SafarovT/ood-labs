#pragma once
#include "IShape.h"

class IGroup : public IShape, IDrawable
{
public:
	virtual ~IGroup() = default;

	virtual size_t GetShapesCount() const = 0;
	virtual size_t InsertShape(std::shared_ptr<IShape> shape) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
	virtual std::shared_ptr<IShape> GetSapeAtIndex(size_t index) = 0;
};