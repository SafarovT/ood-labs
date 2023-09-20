#pragma once
#include <cstdint>
#include <string>
#include "common.h"

class CColor
{
public:
	CColor()
		: m_color("000000")
	{}

	CColor(std::string const& color)
		: m_color(color)
	{}

	std::string GetColor() const
	{
		return m_color;
	}

private:
	std::string m_color;
};