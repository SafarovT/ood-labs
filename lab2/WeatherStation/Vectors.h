#pragma once
#include <cmath>
#include <limits>

struct PolarCoord
{
    double angle = 0.0; // rad
    double length = 0.0;
};

class VectorPolarCoord
{
public:
    VectorPolarCoord() = default;

    VectorPolarCoord(const PolarCoord& coord)
        : m_coord(coord)
    {
    }

    VectorPolarCoord(double angle, double length)
        : m_coord{ angle, length }
    {
    }

    double GetAngle() const
    {
        return m_coord.angle;
    }

    double GetLength() const
    {
        return m_coord.length;
    }

    VectorPolarCoord& operator+=(const VectorPolarCoord& other)
    {
        double x1 = m_coord.length * std::cos(m_coord.angle);
        double y1 = m_coord.length * std::sin(m_coord.angle);

        double x2 = other.m_coord.length * std::cos(other.m_coord.angle);
        double y2 = other.m_coord.length * std::sin(other.m_coord.angle);

        double x = x1 + x2;
        double y = y1 + y2;

        m_coord.length = std::sqrt(x * x + y * y);

        if (m_coord.length > std::numeric_limits<double>::epsilon())
        {
            m_coord.angle = std::atan2(y, x);
        }
        else
        {
            m_coord.angle = 0.0;
        }

        return *this;
    }

    VectorPolarCoord& operator=(const VectorPolarCoord& other) = default;

private:
    PolarCoord m_coord;
};