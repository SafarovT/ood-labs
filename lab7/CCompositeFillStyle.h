#pragma once
#include <functional>
#include "IFillStyle.h"

using FillStyleEnumerator = std::function<void(IFillStyle& style)>;

class CCompositeFillStyle : public IFillStyle
{
public:
	void SetColor(CRGBAColorOptional color) override;
	CRGBAColorOptional GetColor() const override;

protected:
	IFillStyle EmumeratAllStyles() const;

private:

};