#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IParagraph>&& paragraph);
	CConstDocumentItem(std::shared_ptr<IImage>&& image);

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph() const;

	virtual ~CConstDocumentItem() = default;

private:
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
	std::shared_ptr<IImage> m_image = nullptr;
};