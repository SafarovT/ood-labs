#pragma once
#include "ICommandExecuter.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(std::string const& path, int width, int height, ICommandExecuter& commandExecuter)
		: m_path(path)
		, m_width(width)
		, m_height(height)
		, m_commandExecuter(commandExecuter)
	{}

	std::string GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	std::string m_path;

	int m_width, m_height;

	ICommandExecuter& m_commandExecuter;
};

