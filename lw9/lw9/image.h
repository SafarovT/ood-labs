#pragma once
#include <iosfwd>
#include <string>

#include "geom.h"
#include "tile.h"
#include "cow.h"

class Image
{
public:
    /**
     * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
     * ����������� ���������� std::out_of_range.
     */
    explicit Image(Size size, char color = ' ');

    // ���������� ������ ����������� � ��������.
    Size GetSize() const noexcept;

    /**
     * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
     * �����������, ���������� �������.
     */
    char GetPixel(Point p) const noexcept;

    /**
     * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
     * �������� ������������.
     */
    void SetPixel(Point p, char color);

private:
    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, std::ostream& out);

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels);