#pragma once
#include "IStatistic.h"
#include <concepts>
#include <algorithm>

template <typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template <arithmetic T>
class NumericStatistic : public IStatistic<T>
{
public:
	Statistic() {};

	std::string GetMinValue() const override
	{
		return std::to_string(m_minValue);
	}

	std::string GetMaxValue() const override
	{
		return std::to_string(m_maxValue);
	}

	std::string GetAverageValue() const
	{
		return std::to_string(m_accValue / m_countAcc);
	}

	void UpdateData(T value) override
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;
		++m_countAcc;
	}

private:
	T m_minValue = std::numeric_limits<T>::infinity();
	T m_maxValue = -std::numeric_limits<T>::infinity();
	T m_accValue = 0;
	unsigned m_countAcc = 0;
};