#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IParagraph> const& paragraph);
	CConstDocumentItem(std::shared_ptr<IImage> const& image);

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	std::string ToString() const;
	std::string ToHtml() const;

	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
	std::shared_ptr<IImage> m_image = nullptr;
};