#pragma once
#include <iostream>
#include <string>

template <typename T>
class IStatistic
{
public:
	virtual ~IStatistic() {};

	virtual std::string GetMinValue() const = 0;
	virtual std::string GetMaxValue() const = 0;
	virtual std::string GetAverageValue() const = 0;

	virtual void UpdateData(T value) = 0;
};