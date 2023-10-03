#define _USE_MATH_DEFINES
#include "common.h"
#include <format>

namespace
{
	const double AMOUNT_DIGITS_AFTER_POINT = 2;

	void LeftTrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	void RighTrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}
}

std::string Trim(std::string s) {
	RighTrim(s);
	LeftTrim(s);

	return s;
}

std::string DoubleToString(double const number)
{
	double numberToMovePoint = pow(10, AMOUNT_DIGITS_AFTER_POINT);
	double resultNumber = round((number * numberToMovePoint) / numberToMovePoint);

	return std::format("{:.2f}", resultNumber);
}

std::string IntToHexNumber(uint32_t const number)
{
	return std::format("{:#06x}", number);
}

double StringToDouble(std::string numberString)
{
	try
	{
		double number = std::stod(numberString);


		return number;
	}
	catch (std::exception const& ex)
	{
		throw new std::invalid_argument("Parameter cant be converted to number");
	}
}

std::optional<uint32_t> ParseHex(std::string hexString)
{
	try
	{
		uint32_t number = std::stoul(hexString, nullptr, 16);
		
		return number;
	}
	catch (std::invalid_argument const& ex)
	{
	}
	catch (std::out_of_range const& ex)
	{
	}

	return std::nullopt;
}

double RadToDegree(double radValue)
{
	return radValue * 180 / M_PI;
}

std::deque<std::string> Explode(std::string strToExplode, char separator)
{
	auto isElementFound = [](size_t foundIndex)
	{
		return foundIndex != std::string::npos;
	};

	size_t separatorPos = strToExplode.find(separator);
	std::deque<std::string> result;
	while (isElementFound(separatorPos))
	{
		result.push_back(Trim(strToExplode.substr(0, separatorPos)));
		strToExplode = strToExplode.substr(separatorPos + 1);
		separatorPos = strToExplode.find(separator);
	}
	result.push_back(Trim(strToExplode));

	return result;
}