#pragma once
#include "IUndoableEdit.h"
#include <filesystem>
#include <functional>
#include "IImage.h"

class CImage : public IImage
{
public:
	using AddCommandFunction = std::function<void(const IUndoableEditPtr&)>;

	CImage(std::filesystem::path const& path, int width, int height, AddCommandFunction addCommand);

	std::filesystem::path GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

	std::string ToString() const override;

private:
	std::filesystem::path m_savedPath;
	std::filesystem::path m_originPath;
	int m_width, m_height;

	AddCommandFunction m_addCommand;
};

