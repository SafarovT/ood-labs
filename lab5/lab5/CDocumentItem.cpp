#include "CDocumentItem.h"

using namespace std;

CDocumentItem::CDocumentItem(shared_ptr<IParagraph> const& paragraph)
	: CConstDocumentItem(paragraph)
{}

CDocumentItem::CDocumentItem(shared_ptr<IImage> const& image)
	: CConstDocumentItem(image)
{}

shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}

void CDocumentItem::SetDeleted(bool value)
{
	m_isDeleted = value;
}

bool CDocumentItem::IsDeleted() const
{
	return m_isDeleted;
}