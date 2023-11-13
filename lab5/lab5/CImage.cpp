#include "CImage.h"
#include "CFunctionalCommand.h"

using namespace std;

string CImage::GetPath() const
{
	return m_path;
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
	int savedWidth = m_width;
	int savedHeight = m_height;

	m_commandExecuter.AddAndExecuteCommand(make_unique<CFunctionalCommand>(
		[this, width, height]() {
			this->m_width = width;
			this->m_height = height;
		},
		[this, savedWidth, savedHeight]() {
			this->m_width = savedWidth;
			this->m_height = savedHeight;
		}
	));
}