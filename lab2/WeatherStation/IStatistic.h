#pragma once
#include <iostream>

template <typename T>
class IStatistic
{
public:
	virtual ~IStatistic() {};

	virtual void Print() const = 0;

	virtual void UpdateData(T value) = 0;
};