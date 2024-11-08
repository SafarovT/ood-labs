#include "CCompoundEdit.h"
#include <cassert>
#include <ranges>
#include <stdexcept>


CCompoundEdit::CCompoundEdit(const std::optional<std::string>& customName)
{
	if (customName)
	{
		SetName(*customName);
	}
}

CCompoundEdit::~CCompoundEdit()
{
	Destroy();
}

bool CCompoundEdit::CanUndo() const
{
	return CAbstractUndoableEdit::CanUndo() && !m_inProgress;
}

bool CCompoundEdit::CanRedo() const
{
	return CAbstractUndoableEdit::CanRedo() && !m_inProgress;
}

bool CCompoundEdit::AddEditImpl(const IUndoableEditPtr& edit)
{
	assert(edit);

	if (!m_inProgress)
	{
		return false;
	}

	if (!m_edits.empty())
	{
		auto lastEdit = m_edits.back();

		if (!lastEdit->AddEdit(edit))
		{
			if (edit->ReplaceEdit(lastEdit))
			{
				m_edits.pop_back();
			}
			m_edits.push_back(edit);
		}
	}
	else
	{
		m_edits.push_back(edit);
	}

	return true;
}

void CCompoundEdit::EndImpl()
{
}

std::string CCompoundEdit::GetName() const
{
	if (m_edits.empty() || m_hasCustomName)
	{
		return CAbstractUndoableEdit::GetName();
	}
	return m_edits.front()->GetName();
}

void CCompoundEdit::End()
{
	m_inProgress = false;
	EndImpl();
}

void CCompoundEdit::DestroyImpl() noexcept
{
	for (auto& edit : m_edits | std::views::reverse)
	{
		edit->Destroy();
	}
	m_edits.clear();
}

void CCompoundEdit::UndoImpl()
{
	for (auto& edit : m_edits | std::views::reverse)
	{
		edit->Undo();
	}
}

void CCompoundEdit::RedoImpl()
{
	for (auto& edit : m_edits)
	{
		edit->Redo();
	}
}

void CCompoundEdit::SetName(const std::string& name)
{
	CAbstractUndoableEdit::SetName(name);
	m_hasCustomName = true;
}

size_t CCompoundEdit::GetEditCount() const
{
	return m_edits.size();
}

IUndoableEditPtr CCompoundEdit::GetEdit(size_t index) const
{
	if (index >= m_edits.size())
	{
		throw std::invalid_argument("Index is out of range");
	}

	return m_edits[index];
}