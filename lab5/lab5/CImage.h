#pragma once
#include <filesystem>
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(std::filesystem::path const& path, int width, int height);
	~CImage();

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

	std::string ToString() const override;

private:
	std::filesystem::path m_tempPath;
	std::filesystem::path m_originPath;
	int m_width, m_height;
};

