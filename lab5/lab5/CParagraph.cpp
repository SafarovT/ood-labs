#include "CParagraph.h"
#include "CFunctionalCommand.h"

using namespace std;

string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(std::string const& text)
{
	string savedText = m_text;

	m_commandExecuter.AddAndExecuteCommand(make_unique<CFunctionalCommand>(
		[this, text]() {
			this->m_text = text;
		},
		[this, savedText]() {
			this->m_text = savedText;
		}
	));
}