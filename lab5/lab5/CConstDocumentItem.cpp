#include "CConstDocumentItem.h"
#include <unordered_map>

using namespace std;

namespace
{
	const unordered_map<char, string> HTML_ESCAPE_MAP =
	{
		{'&', "&amp;"},
		{'<', "&lt;"},
		{'>', "&gt;"},
		{'\"', "&quot;"},
		{'\'', "&#39;"}
	};

	string EscapeHtml(const string& input)
	{
		string result;
		result.reserve(input.size());

		for (char c : input)
		{
			auto it = HTML_ESCAPE_MAP.find(c);
			if (it != HTML_ESCAPE_MAP.end())
			{
				result += it->second;
			}
			else
			{
				result += c;
			}
		}

		return result;
	}
}

CConstDocumentItem::CConstDocumentItem(shared_ptr<IParagraph> const& paragraph)
	: m_paragraph(paragraph)
{}

CConstDocumentItem::CConstDocumentItem(shared_ptr<IImage> const& image)
	: m_image(image)
{}

shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}

string CConstDocumentItem::ToString() const
{
	if (m_paragraph != nullptr)
	{
		return m_paragraph->ToString();
	}

	return m_image->ToString();
}

string CConstDocumentItem::ToHtml() const
{
	string result;
	if (m_image != nullptr)
	{
		string widthStr = to_string(m_image->GetWidth());
		string heightStr = to_string(m_image->GetHeight());
		string pathStr = m_image->GetPath().generic_string();
		pathStr.pop_back();
		result = "<img width=" + widthStr + " height=" + heightStr + " src=" + pathStr + "/>";
	}
	if (m_paragraph)
	{
		result = "<p>" + EscapeHtml(m_paragraph->GetText()) + "</p>";
	}

	return result;
}