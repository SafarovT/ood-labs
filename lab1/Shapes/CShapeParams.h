#pragma once
#include <string>
#include <vector>
#include "common.h"

class CShapeParams
{
public:
	CShapeParams(std::vector<double>&& params)
		: m_params(std::move(params))
		, m_text("")
	{}

	CShapeParams(std::vector<double>&& params, std::string&& text)
		: m_params(std::move(params))
		, m_text(std::move(text))
	{}

	std::vector<double> GetParams() const
	{
		return m_params;
	}

	std::string GetParamsStr() const
	{
		std::string result;
		for (double param : m_params)
		{
			result += DoubleToString(param) + " ";
		}
		result += m_text;

		return result;
	}

	std::string GetText() const
	{
		return m_text;
	}

private:
	std::vector<double> m_params;
	std::string m_text;
};