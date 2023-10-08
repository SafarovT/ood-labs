#pragma once
#include "IStatistic.h"
#include <algorithm>

class NumericStatistic : public IStatistic<double>
{
public:
	double GetMax() const override
	{
		return m_maxValue;
	}

	double GetMin() const override
	{
		return m_minValue;
	}

	double GetAverage() const override
	{
		return m_accValue;
	}

	void UpdateData(double value) override
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
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};