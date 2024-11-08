#include <fstream>
#include <iostream>
#include "CDocument.h"
#include "Edits.h"
#include "CParagraph.h"
#include "CImage.h"

using namespace std;

size_t CDocument::GetItemsCount()const
{
	return m_items.size();
}

void CDocument::CheckElementAtIndex(size_t index) const
{
	if (index > GetItemsCount())
	{
		throw invalid_argument("No elemnt with given index");
	}
}

void CDocument::CheckOverflowBeforeInsert() const
{
	if (m_items.size() == SIZE_MAX)
	{
		throw invalid_argument("You can not insert more elements in document");
	}
}

void CDocument::DeleteItem(size_t index)
{
	CheckElementAtIndex(index);
	auto iter = m_items.begin();
	advance(iter, index);
	m_history.AddEdit(make_shared<CDeleteItemEdit>(iter, make_shared<list<CDocumentItem>>(m_items)));
}

void CDocument::InsertParagraph(const string& text, optional<size_t> position = nullopt)
{
	CheckOverflowBeforeInsert();
	auto iter = m_items.begin();
	if (position != nullopt)
	{
		advance(iter, *position);
	}
	else
	{
		iter = m_items.end();
	}
	auto paragraph = CParagraph(text);
	m_history.AddEdit(make_shared<CInsertItemEdit>(paragraph, iter, make_shared<list<CDocumentItem>>(m_items)));
}

void CDocument::InsertImage(const string& path, int width, int height, optional<size_t> position = nullopt)
{
	auto iter = m_items.begin();
	if (position != nullopt)
	{
		advance(iter, *position);
	}
	else
	{
		iter = m_items.end();
	}
	auto paragraph = CImage(path, width, height);
	m_history.AddEdit(make_shared<CInsertItemEdit>(paragraph, iter, make_shared<list<CDocumentItem>>(m_items)));
}

void CDocument::ResizeImage(int width, int height, size_t index)
{
	CheckElementAtIndex(index);
	auto iter = m_items.begin();
	advance(iter, index);
	m_history.AddEdit(make_shared<CResizeImageEdit>(iter->GetImage(), width, height));
}

void CDocument::ReplaceText(const std::string& text, size_t index)
{
	CheckElementAtIndex(index);
	auto iter = m_items.begin();
	advance(iter, index);
	m_history.AddEdit(make_shared<CReplaceTextEdit>(iter->GetParagraph(), text));
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	CheckElementAtIndex(index);
	auto iter = m_items.begin();
	advance(iter, index);
	return *iter;
}

CDocumentItem CDocument::GetItem(size_t index)
{
	CheckElementAtIndex(index);
	auto iter = m_items.begin();
	advance(iter, index);
	return *iter;
}

string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::SetTitle(const string& title)
{
	m_history.AddEdit(make_shared<CChangeTitleEdit>(
		make_shared<CDocument>(this),
		title,
		[&](const string& newTitle) { m_title = newTitle; }
	));
}

bool CDocument::CanUndo()const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo()const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::List() const
{
	size_t index = 1;
	cout << "Title: " << GetTitle() << endl;
	for (const auto& item : m_items)
	{
		cout << index++ << ". " << item.ToString() << endl;
	}
}

void CDocument::Save(const string& path) const
{
	std::ofstream file;
	file.open(path);

	if (!file.is_open())
	{
		throw runtime_error("Failed to open html file.");
	}

	file << "<!DOCTYPE html>" << endl
		<< "<html lang=\"en\">" << endl
		<< "<head>" << endl
		<< "    <meta charset=\"UTF-8\">" << endl
		<< "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl
		<< "    <title>" << m_title << "</title>" << endl
		<< "</head>" << endl
		<< "<body>" << endl;

	for (const auto& item : m_items)
	{
		file << item.ToHtml() << endl;
	}

	file << "</body>" << endl;
	file << "</html>" << endl;

	if (!file.flush())
	{
		throw runtime_error("Failed to write in output file");
	}
}