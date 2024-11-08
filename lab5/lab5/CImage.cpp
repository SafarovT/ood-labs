#include "CImage.h"

using namespace std;

CImage::CImage(filesystem::path const& path, int width, int height)
	: m_originPath(path)
	, m_width(width)
	, m_height(height)
{
	filesystem::path currentPath = filesystem::current_path();

	filesystem::path imagesFolder = currentPath / "images";

	if (!filesystem::exists(imagesFolder))
	{
		filesystem::create_directory(imagesFolder);
	}

	m_tempPath = imagesFolder / path.filename();
	filesystem::copy(path, m_tempPath, filesystem::copy_options::overwrite_existing);
}

CImage::~CImage()
{
	filesystem::remove(m_tempPath);
}

filesystem::path CImage::GetPath() const
{
	return m_originPath;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

string CImage::ToString() const
{
	string widthStr = to_string(GetWidth());
	string heightStr = to_string(GetHeight());
	string pathStr = GetPath().generic_string();
	return "Image" + widthStr + " " + heightStr + " " + pathStr;
}
