#pragma once
#include "CRGBAColor.h"

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;
	virtual void SetColor(CRGBAColorOptional color) = 0;
	virtual CRGBAColorOptional GetColor() const = 0;
};