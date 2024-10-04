#pragma once
#include "IStatistic.h"
#include "Vectors.h"

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

		VectorCartesianCoord oldVector(m_sumVector.ToCartesian());
		VectorCartesianCoord newVector(value.ToCartesian());
		VectorCartesianCoord resultVector = oldVector + newVector;
		m_accCount++;
		m_sumVector = VectorPolarCoord(resultVector.ToPolar()) / m_accCount;
	}

private:
	VectorPolarCoord m_maxLengthVector = VectorPolarCoord({ 0, -std::numeric_limits<double>::infinity() });
	VectorPolarCoord m_minLengthVector = VectorPolarCoord({ 0, std::numeric_limits<double>::infinity() });
	VectorPolarCoord m_sumVector = VectorPolarCoord({ 0, 0 });
	double m_accCount = 0;
};

