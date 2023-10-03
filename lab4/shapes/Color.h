#pragma once
#include <stdexcept>
#include <string>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

Color StrToColor(std::string const& str)
{
	if (str == "Green")
	{
		return Color::Green;
	}
	if (str == "Red")
	{
		return Color::Red;
	}
	if (str == "Blue")
	{
		return Color::Blue;
	}
	if (str == "Yellow")
	{
		return Color::Yellow;
	}
	if (str == "Pink")
	{
		return Color::Pink;
	}
	if (str == "Black")
	{
		return Color::Black;
	}

	throw new std::exception("Unknown color name");
}

std::string ColorToStr(Color color)
{
	switch (color)
	{
	case Color::Green:
		return "Green";
	case Color::Red:
		return "Red";
	case Color::Blue:
		return "Blue";
	case Color::Yellow:
		return "Yellow";
	case Color::Pink:
		return "Pink";
	case Color::Black:
		return "Black";
	default:
		return "Black";
	}
}