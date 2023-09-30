#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <math.h>


struct PolarCoord
{
	double angle = 0;
	double length = 0;
};

struct CartesianCoord
{
	double x = 0;
	double y = 0;
};

class VectorCartesianCoord
{
public:
	VectorCartesianCoord(CartesianCoord coord)
		: m_data(coord)
	{}

	VectorCartesianCoord operator +(VectorCartesianCoord const& vector) const
	{
		return VectorCartesianCoord({ m_data.x + vector.m_data.x, m_data.y + vector.m_data.y });
	}

	PolarCoord ToPolar() const
	{
		double length = sqrt(m_data.x * m_data.x + m_data.y * m_data.y);
		double angleRad = asin(m_data.x / length);
		double angleDeg = angleRad * 180 / M_PI;

		return { angleDeg, length };
	}

private:
	CartesianCoord m_data;
};

class VectorPolarCoord
{
public:
	VectorPolarCoord(PolarCoord coord)
		: m_data(coord)
	{}

	VectorPolarCoord operator /(double number)
	{
		return VectorPolarCoord({ m_data.angle, m_data.length / number });
	}

	double GetLength() const
	{
		return m_data.length;
	}

	double GetAngle() const
	{
		return m_data.angle;
	}

	CartesianCoord ToCartesian() const
	{
		double angleRad = m_data.angle * M_PI / 180;
		double x = m_data.length * cos(angleRad);
		double y = m_data.length * sin(angleRad);

		return { x, y };
	}

private:
	PolarCoord m_data;
};
