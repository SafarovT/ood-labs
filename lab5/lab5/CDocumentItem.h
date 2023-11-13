#pragma once
#include "CConstDocumentItem.h"

class CDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph>&& paragraph);
	CDocumentItem(std::shared_ptr<IImage>&& image);

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();

private:
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
	std::shared_ptr<IImage> m_image = nullptr;
};