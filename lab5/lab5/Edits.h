#pragma once
#include <functional>
#include "CAbstractUndoableEdit.h"
#include "IDocument.h"
#include "IImage.h"
#include "IParagraph.h"

#include <iostream>

class CChangeTitleEdit : public CAbstractUndoableEdit
{
public:
	CChangeTitleEdit(IDocument* document, const std::string& newTitle, std::function<void(const std::string&)> changeTitle)
		: m_document(document)
		, m_prevTitle(document->GetTitle())
		, m_newTitle(newTitle)
		, m_changeTitle(changeTitle)
	{}

	void RedoImpl() override
	{
		m_changeTitle(m_newTitle);
	}

	void UndoImpl() override
	{
		m_changeTitle(m_prevTitle);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto prev = dynamic_cast<CChangeTitleEdit*>(edit.get()); prev != nullptr && m_document == prev->m_document)
		{
			m_prevTitle = prev->m_prevTitle;
			return true;
		}

		return false;
	}

private:
	IDocument* m_document;
	std::string m_prevTitle, m_newTitle;
	std::function<void(const std::string&)> m_changeTitle;
};

class CInsertItemEdit : public CAbstractUndoableEdit
{
public:
	CInsertItemEdit(CDocumentItem item, std::vector<CDocumentItem>::iterator iter, std::vector<CDocumentItem>& vector)
		: m_item(item)
		, m_iter(iter)
		, m_vector(vector)
	{}

	void RedoImpl() override
	{
		m_iter = m_vector.insert(m_iter, m_item);
	}

	void UndoImpl() override
	{
		m_iter = m_vector.erase(m_iter);
	}

	void DestroyImpl() noexcept override
	{
		if (!IsExecuted())
		{
			m_item.Delete();
		}
	}

private:
	CDocumentItem m_item;
	std::vector<CDocumentItem>::iterator m_iter;
	std::vector<CDocumentItem>& m_vector;
};

class CReplaceTextEdit : public CAbstractUndoableEdit
{
public:
	CReplaceTextEdit(IParagraph* paragraph, const std::string& newText, std::function<void(const std::string&)> replaceText)
		: m_paragraph(paragraph)
		, m_prevText(paragraph->GetText())
		, m_newText(newText)
		, m_replaceText(replaceText)
	{
	}

	void RedoImpl() override
	{
		m_replaceText(m_newText);
	}

	void UndoImpl() override
	{
		m_replaceText(m_prevText);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto prev = dynamic_cast<CReplaceTextEdit*>(edit.get()); prev != nullptr && prev->m_paragraph == m_paragraph)
		{
			m_prevText = prev->m_prevText;
			return true;
		}

		return false;
	}

private:
	IParagraph* m_paragraph;
	std::string m_prevText, m_newText;
	std::function<void(const std::string&)> m_replaceText;
};

class CResizeImageEdit : public CAbstractUndoableEdit
{
public:
	CResizeImageEdit(IImage* image, int newWidth, int newHeight, std::function<void(int, int)> resizeImage)
		: m_image(image)
		, m_newWidth(newWidth)
		, m_newHeight(newHeight)
		, m_prevWidth(image->GetWidth())
		, m_prevHeight(image->GetHeight())
		, m_resizeImage(resizeImage)
	{}

	void RedoImpl() override
	{
		m_resizeImage(m_newWidth, m_newHeight);
	}

	void UndoImpl() override
	{
		m_resizeImage(m_prevWidth, m_prevHeight);
	}

	bool ReplaceEditImpl(const IUndoableEditPtr& edit) override
	{
		if (const auto prev = dynamic_cast<CResizeImageEdit*>(edit.get()); prev != nullptr && prev->m_image == m_image)
		{
			m_prevWidth = prev->m_prevWidth;
			m_prevHeight = prev->m_prevHeight;

			return true;
		}

		return false;
	}

private:
	int m_newWidth, m_newHeight, m_prevWidth, m_prevHeight;
	IImage* m_image;
	std::function<void(int, int)> m_resizeImage;
};

class CDeleteItemEdit : public CAbstractUndoableEdit
{
public:
	CDeleteItemEdit(std::vector<CDocumentItem>::iterator iter, std::vector<CDocumentItem>& vector)
		: m_item(*iter)
		, m_iter(iter)
		, m_vector(vector)
	{}

	void RedoImpl() override
	{
		m_iter = m_vector.erase(m_iter);
	}

	void UndoImpl() override
	{
		m_iter = m_vector.insert(m_iter, m_item);
	}

	void DestroyImpl() noexcept override
	{
		if (IsExecuted())
		{
			m_item.Delete();
		}
	}

private:
	CDocumentItem m_item;
	std::vector<CDocumentItem>::iterator m_iter;
	std::vector<CDocumentItem>& m_vector;
};