#pragma once
#include <array>
#include <cassert>

#include "geom.h"

class Tile
{
public:
	// ������ ����� 8*8 ��������.
	constexpr static int SIZE = 8;

	// ����������� �� ���������. ��������� ���� ��������� ������.
	Tile(char color = ' ') noexcept
		: m_pixels(std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, color)))
	{
		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	Tile(const Tile& other)
		: m_pixels(other.m_pixels)
	{
		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	~Tile()
	{
		// -------------- �� ������� ------------
		--m_instanceCount; // ��������� ������� ������.
		assert(m_instanceCount >= 0);
		// -------------- �� ������� ------------
	}

	/**
	 * �������� ���� ������� �����.
	 * ���� ���������� ������� �� ������� �����, ����� ������ �� ������.
	 */
	void SetPixel(Point p, char color) noexcept
	{
		if (p.x < 0 || p.x >= SIZE || p.y < 0 || p.y >= SIZE)
		{
			throw std::out_of_range("Addressing out of range pixel");
		}
		m_pixels[p.x][p.y] = color;
	}

	/**
	 * ���������� ���� �������. ���� ���������� ������� �� ������� �����, ������������ ������.
	 */
	char GetPixel(Point p) const noexcept
	{
		if (p.x < 0 || p.x >= SIZE || p.y < 0 || p.y >= SIZE)
		{
			throw std::out_of_range("Addressing out of range tile pixel");
		}
		return m_pixels[p.x][p.y];
	}

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept
	{
		// -------------- �� ������� ------------
		return m_instanceCount;
		// -------------- �� ������� ------------
	}

private:
	// -------------- �� ������� ------------
	inline static int m_instanceCount = 0;
	// -------------- �� ������� ------------

	/* ���������� ����� ���� ��� �������� �������� �����. */
	std::vector<std::vector<char>> m_pixels;
};