#pragma once
#include <string>
#include <filesystem>

class IImage
{
public:
	// Возвращает путь относительно каталога документа
	virtual std::filesystem::path GetPath() const = 0;
	// Ширина изображения в пикселях
	virtual int GetWidth() const = 0;
	// Высота изображения в пикселях
	virtual int GetHeight() const = 0;
	// Изменяет размер изображения
	virtual void Resize(int width, int height) = 0;
	virtual void Delete() = 0;
	virtual std::string ToString() const = 0;
	virtual ~IImage() = default;
};