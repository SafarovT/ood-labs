#pragma once
#include <cstdint>
#include <string>
#include "common.h"

class CColor
{
public:
	CColor(uint32_t color)
		: m_color(color)
	{}

	uint32_t GetColor() const
	{
		return m_color;
	}

	std::string GetColorStr() const
	{
		return IntToHexNumber(m_color);
	}

private:
	uint32_t m_color;
};