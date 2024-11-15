#pragma once
#include <filesystem>
#include "IImage.h"
#include "CUndoManager.h"

class CImage : public IImage
{
public:
	CImage(std::filesystem::path const& path, int width, int height, AddCommandFunction addCommand);

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

	std::string ToString() const override;

private:
	std::filesystem::path m_savedPath;
	int m_width, m_height;
	AddCommandFunction m_addCommand;
};

