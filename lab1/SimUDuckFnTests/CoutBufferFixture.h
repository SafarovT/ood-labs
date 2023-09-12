#pragma once
#include <iostream>
#include <sstream>

class CoutBufferFixture
{
public:
	~CoutBufferFixture();

	std::string GetBufferValue();

	void ClearBuffer();

private:
	std::stringstream m_buffer;
	std::streambuf* m_backupBuffer = std::cout.rdbuf(m_buffer.rdbuf());
};