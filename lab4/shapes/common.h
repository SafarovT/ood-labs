#pragma once
#include <math.h>
#include <string>
#include <optional>
#include <vector>
#include <deque>

std::string DoubleToString(double const number);
std::string IntToHexNumber(uint32_t const number);
double StringToDouble(std::string numberString);
std::optional<uint32_t> ParseHex(std::string hexString);
std::string Trim(std::string s);
double RadToDegree(double radValue);
std::deque<std::string> Explode(std::string strToExplode, char separator);