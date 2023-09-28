#pragma once
#include "IStatistic.h"

struct VectorCartesianCoord
{
	double x = 0;
	double y = 0;
};

class VectorPolarCoord
{
public:
	std::string ToStr() const
	{
		return std::to_string(m_length) + ", " + std::to_string(m_length) + "°";
	}

	VectorCartesianCoord

	double m_angle = 0;
	double m_length = 0;
};

class VectorAngleStatistic : public IStatistic<VectorPolarCoord>
{
public:
	
	std::string GetMinValue() const override
	{
		return m_minLengthVector.ToStr();
	}

	std::string GetMaxValue() const override
	{
		return m_maxLengthVector.ToStr();
	}

	std::string GetAverageValue() const override
	{
		return m_sumVector.ToStr();
	}

	void UpdateData(VectorPolarCoord value) override
	{

	}

private:
	VectorPolarCoord m_maxLengthVector = { 0, 0 };
	VectorPolarCoord m_minLengthVector = { 0, 0 };
	VectorPolarCoord m_sumVector = { 0, 0 };
};

