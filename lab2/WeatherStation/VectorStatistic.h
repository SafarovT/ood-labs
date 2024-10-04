#pragma once
#include "IStatistic.h"
#include "Vectors.h"

#include <iostream>

class VectorStatistic : public IStatistic<double>
{
public:
	double GetMax() const override
	{
		return m_maxLengthVector.GetLength();
	}

	double GetMin() const override
	{
		return m_minLengthVector.GetLength();
	}

	double GetAverage() const override
	{
		return m_sumVector.GetAngle();
	}
	
	void UpdateData(VectorPolarCoord value)
	{
		if (value.GetLength() > m_maxLengthVector.GetLength())
		{
			m_maxLengthVector = value;
		}
		if (value.GetLength() < m_minLengthVector.GetLength())
		{
			m_minLengthVector = value;
		}

		m_sumVector += value;
	}

private:
	VectorPolarCoord m_maxLengthVector = VectorPolarCoord({ 0, -std::numeric_limits<double>::infinity() });
	VectorPolarCoord m_minLengthVector = VectorPolarCoord({ 0, std::numeric_limits<double>::infinity() });
	VectorPolarCoord m_sumVector = VectorPolarCoord({ 0, 0 });
};

