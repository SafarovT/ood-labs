#pragma once
#include "IFillStyle.h"

class CFillStyle : public IFillStyle
{
public:
	CFillStyle(CRGBAColorOptional color)
		: m_color(color)
	{}

	void SetColor(CRGBAColorOptional color) override
	{
		m_color = color;
	}

	CRGBAColorOptional GetColor() const override
	{
		return m_color;
	}
	
private:
	CRGBAColorOptional m_color = std::nullopt;
};
