#pragma once
#include "IStatistic.h"
#include "Vectors.h"

class VectorStatistic : public IStatistic<VectorPolarCoord>
{
public:
	VectorStatistic(std::string const& angleName, std::string const& lengthName)
		: m_angleName(angleName)
		, m_lengthName(lengthName)
	{}
	
	void Print() const override
	{
		std::cout << "Max " << GetVectorStr(m_maxLengthVector) << std::endl;
		std::cout << "Min " << GetVectorStr(m_minLengthVector) << std::endl;
		std::cout << "Average " << GetVectorStr(m_sumVector) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void UpdateData(VectorPolarCoord value) override
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

	std::string m_angleName;
	std::string m_lengthName;

	std::string GetVectorStr(VectorPolarCoord vector) const
	{
		return m_lengthName + " " + std::to_string(vector.GetLength()) + " " + m_angleName + " " + std::to_string(vector.GetAngle());
	}
};

