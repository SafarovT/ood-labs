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
	void Delete() noexcept override;

	std::string ToString() const override;

private:
	std::filesystem::path m_savedPath;
	int m_width, m_height;
	bool m_isDeleted = false;
	AddCommandFunction m_addCommand;
};

