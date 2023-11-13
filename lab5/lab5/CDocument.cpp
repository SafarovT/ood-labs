#include "CDocument.h"

using namespace std;

shared_ptr<IParagraph> CDocument::InsertParagraph(const string& text, optional<size_t> position = nullopt)
{

}

shared_ptr<IImage> CDocument::InsertImage(const string& path, int width, int height, optional<size_t> position = nullopt)
{

}

size_t CDocument::GetItemsCount()const
{

}

CConstDocumentItem CDocument::GetItem(size_t index)const
{

}

CDocumentItem CDocument::GetItem(size_t index)
{

}

void CDocument::DeleteItem(size_t index)
{

}

string CDocument::GetTitle()const
{

}

void CDocument::SetTitle(const string& title)
{

}

bool CDocument::CanUndo()const
{

}

void CDocument::Undo()
{

}

bool CDocument::CanRedo()const
{

}

void CDocument::Redo()
{

}

void CDocument::Save(const string& path) const
{

}