#pragma once
#include <string>

class CClient
{
public:
	std::string GetMemberName() const
	{
		return m_memberName;
	}
private:
	std::string m_memberName;
};