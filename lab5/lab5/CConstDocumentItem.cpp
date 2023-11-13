#include "CConstDocumentItem.h"

using namespace std;

CConstDocumentItem::CConstDocumentItem(shared_ptr<IParagraph>&& paragraph)
	: m_paragraph(paragraph)
{}

CConstDocumentItem::CConstDocumentItem(shared_ptr<IImage>&& image)
	: m_image(image)
{}

shared_ptr<IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

shared_ptr<IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}