#include "CoutBufferFixture.h"

CoutBufferFixture::~CoutBufferFixture()
{
	std::cout.rdbuf(m_backupBuffer);
}

std::string CoutBufferFixture::GetBufferValue()
{
	return m_buffer.str();
}

void CoutBufferFixture::ClearBuffer()
{
	m_buffer.str("");
}