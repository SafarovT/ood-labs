#pragma once
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text)
		: m_text(text)
	{}

	std::string GetText() const override;
	void SetText(const std::string& text) override;
	std::string ToString() const override;
private:
	std::string m_text;
};
