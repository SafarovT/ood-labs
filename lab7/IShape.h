#pragma once
#include <memory>
#include "IDrawable.h"
#include "IGroup.h"
#include "Rect.h"

class IShape : public IDrawable
{
public:
	virtual ~IShape() = default;

	virtual void SetFrame(const Rect& frame) = 0;
	virtual Rect GetFrame() = 0;

	// TODO:

	// TODO:
	virtual std::shared_ptr<IGroup> GetGroup() = 0;
};