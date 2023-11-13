#pragma once
#include "IParagraph.h"
#include "ICommandExecuter.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(std::string const& text, ICommandExecuter& commandExcecuter)
		: m_text(text)
		, m_commandExecuter(commandExcecuter)
	{}

	std::string GetText() const override;
	void SetText(const std::string& text) override;
private:
	std::string m_text;

	ICommandExecuter& m_commandExecuter;
};
