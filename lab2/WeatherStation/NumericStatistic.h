#pragma once
#include "IStatistic.h"
#include <algorithm>

class NumericStatistic : public IStatistic<double>
{
public:
	NumericStatistic(std::string const& name)
		: m_name(name)
	{};

	void Print() const override
	{
		std::cout << "Max " << m_name << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
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

	std::string m_name;
};