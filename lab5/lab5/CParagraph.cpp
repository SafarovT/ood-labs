#include "CParagraph.h"
#include "Edits.h"

using namespace std;

string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(string const& text)
{
	auto command = make_shared<CReplaceTextEdit>(this, text, [&](const string newText) { m_text = newText; });
	command->RedoImpl();
	m_addCommand(command);
}

string CParagraph::ToString() const
{
	return "Paragraph: " + GetText();
}