#include "CImage.h"
#include "Edits.h"

using namespace std;

CImage::CImage(filesystem::path const& path, int width, int height, AddCommandFunction addCommand)
	: m_originPath(path)
	, m_width(width)
	, m_height(height)
	, m_addCommand(std::move(addCommand))
{
	filesystem::path currentPath = filesystem::current_path();

	filesystem::path imagesFolder = currentPath / "images";

	if (!filesystem::exists(imagesFolder))
	{
		filesystem::create_directory(imagesFolder);
	}

	m_savedPath = imagesFolder / m_originPath.filename();

	filesystem::copy(m_originPath, m_savedPath, filesystem::copy_options::overwrite_existing);
}

filesystem::path CImage::GetPath() const
{
	return m_savedPath;
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

	m_addCommand(make_shared<CResizeImageEdit>(
		this,
		width,
		height,
		[&](int newWidth, int newHeight) { m_width = newWidth; m_height = newHeight; }
	));
}

string CImage::ToString() const
{
	string widthStr = to_string(GetWidth());
	string heightStr = to_string(GetHeight());
	string pathStr = GetPath().generic_string();
	return "Image" + widthStr + " " + heightStr + " " + pathStr;
}
