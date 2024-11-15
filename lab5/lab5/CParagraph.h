#pragma once
#include "IParagraph.h"
#include "CUndoManager.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text, AddCommandFunction addCommand)
		: m_text(text)
		, m_addCommand(std::move(addCommand))
	{}

	std::string GetText() const override;
	void SetText(const std::string& text) override;
	std::string ToString() const override;
private:
	std::string m_text;
	AddCommandFunction m_addCommand;
};
