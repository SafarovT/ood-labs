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

vector<CDocumentItem>::iterator CDocument::GetIterAtIndex(size_t index)
{
	if (index >= GetItemsCount())
	{
		throw out_of_range("Error position of element.");
	}
	return next(m_items.begin(), index);
}

void CDocument::CheckElementAtIndex(size_t index) const
{
	if (index >= GetItemsCount())
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
	auto iter = GetIterAtIndex(index);
	auto command = make_shared<CDeleteItemEdit>(iter, m_items);
	command->RedoImpl();
	m_history.AddEdit(command);
}

void CDocument::InsertParagraph(const string& text, optional<size_t> position)
{
	CheckOverflowBeforeInsert();
	auto iter = position != nullopt
		? GetIterAtIndex(*position)
		: m_items.end();
	auto item = CDocumentItem(make_shared<CParagraph>(text, [&](const IUndoableEditPtr& edit) {m_history.AddEdit(edit); }));
	auto command = make_shared<CInsertItemEdit>(item, iter, m_items);
	command->RedoImpl();
	m_history.AddEdit(command);
}

void CDocument::InsertImage(const string& path, int width, int height, optional<size_t> position)
{
	CheckOverflowBeforeInsert();
	auto iter = position != nullopt
		? GetIterAtIndex(*position)
		: m_items.end();
	auto item = CDocumentItem(make_shared<CImage>(path, width, height, [&](const IUndoableEditPtr& edit) {m_history.AddEdit(edit); }));
	auto command = make_shared<CInsertItemEdit>(item, iter, m_items);
	command->RedoImpl();
	m_history.AddEdit(command);
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
	auto command = make_shared<CChangeTitleEdit>(
		this,
		title,
		[&](const string& newTitle) { m_title = newTitle; }
	);
	command->RedoImpl();
	m_history.AddEdit(command);
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
	size_t index = 0;
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