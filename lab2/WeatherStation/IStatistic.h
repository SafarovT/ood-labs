#pragma once
#include <iostream>

template <typename T>
class IStatistic
{
public:
	virtual ~IStatistic() {};

	virtual T GetMin() const = 0;
	virtual T GetMax() const = 0;
	virtual T GetAverage() const = 0;

	virtual void UpdateData(T value) = 0;
};