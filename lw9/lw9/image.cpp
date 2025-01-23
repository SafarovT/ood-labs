#include "image.h"
#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 * Конструирует изображение заданного размера. Если размеры не являются положительными,
 * выбрасывает исключение std::out_of_range.
 */
Image::Image(Size size, char color)
	: m_size(size)
{
	if (size.height <= 0 || size.width <= 0)
	{
		throw std::out_of_range("Cannot create image less than 1 px width and height");
	}

	int tilesInColum = size.width / Tile::SIZE + (size.width % Tile::SIZE ? 1 : 0);
	int tilesInRow = size.height / Tile::SIZE + (size.height % Tile::SIZE ? 1 : 0);

	m_tiles = std::vector<std::vector<CoW<Tile>>>
		(
			tilesInColum, std::vector<CoW<Tile>>(tilesInRow, CoW(Tile(color)))
		);
}

// Возвращает размер изображения в пикселях.
Size Image::GetSize() const noexcept
{
	return { m_size.width, m_size.height };
}

/**
 * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
 * изображения, возвращает «пробел».
 */
char Image::GetPixel(Point p) const noexcept
{
	if (p.x < 0 || p.x > m_size.width || p.y < 0 || p.y > m_size.height)
	{
		throw std::out_of_range("Out of range pixel position");
	}

	int tileColumIndex = p.x / Tile::SIZE;
	int pixelColumIndex = p.x % Tile::SIZE;
	int tileRowIndex = p.y / Tile::SIZE;
	int pixelRowIndex = p.y % Tile::SIZE;

	return m_tiles[tileColumIndex][tileRowIndex]->GetPixel({ pixelColumIndex, pixelRowIndex });
}

/**
 * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
 * действие игнорируется.
 */
void Image::SetPixel(Point p, char color)
{
	if (p.x < 0 || p.x > m_size.width || p.y < 0 || p.y > m_size.height)
	{
		throw std::out_of_range("Out of range pixel position");
	}

	int tileColumIndex = p.x / Tile::SIZE;
	int pixelColumIndex = p.x % Tile::SIZE;
	int tileRowIndex = p.y / Tile::SIZE;
	int pixelRowIndex = p.y % Tile::SIZE;

	auto oldColor = m_tiles[tileColumIndex][tileRowIndex]->GetPixel({ pixelColumIndex, pixelRowIndex });

	m_tiles[tileColumIndex][tileRowIndex].Write()->SetPixel({ pixelColumIndex, pixelRowIndex }, color ^ oldColor);
}

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y })); // put ???
		}
		out.put('\n');
	}
}

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}