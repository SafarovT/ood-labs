#include "CUndoManager.h"
#include <cassert>

bool CUndoManager::CanUndo() const
{
	if (m_inProgress)
	{
		const auto& edit = GetEditToBeUndone();
		return edit && edit->CanUndo();
	}

	return CCompoundEdit::CanUndo();
}

bool CUndoManager::CanRedo() const
{
	if (m_inProgress)
	{
		const auto& edit = GetEditToBeRedone();
		return edit && edit->CanRedo();
	}
	
	return CCompoundEdit::CanRedo();
}

size_t CUndoManager::GetCurrentEditIndex() const
{
	return m_indexOfNextAdd;
}

void CUndoManager::Clear()
{
	m_edits.clear();
	m_indexOfNextAdd = 0;
}

IUndoableEditPtr CUndoManager::GetEditToBeUndone() const
{
	assert(m_indexOfNextAdd <= m_edits.size());
	return (m_indexOfNextAdd > 0) ? m_edits[m_indexOfNextAdd - 1] : nullptr;
}

IUndoableEditPtr CUndoManager::GetEditToBeRedone() const
{
	return (m_indexOfNextAdd < m_edits.size()) ? m_edits[m_indexOfNextAdd] : nullptr;
}

void CUndoManager::UndoTo(const IUndoableEditPtr& edit)
{
	IUndoableEditPtr nextEdit;
	do
	{
		assert(m_indexOfNextAdd > 0 && m_indexOfNextAdd <= m_edits.size());
		nextEdit = m_edits[--m_indexOfNextAdd];
		nextEdit->Undo();
	} while (nextEdit != edit);
}

void CUndoManager::RedoTo(const IUndoableEditPtr& edit)
{
	IUndoableEditPtr nextEdit;
	do
	{
		assert(m_indexOfNextAdd < m_edits.size());
		nextEdit = m_edits[m_indexOfNextAdd++];
		nextEdit->Redo();
	} while (nextEdit != edit);
}

void CUndoManager::TrimEdits(size_t from, size_t to)
{
	assert(from <= to);
	assert(to <= m_edits.size());
	auto i = to;
	while (i > from)
	{
		const auto& edit = m_edits[--i];
		edit->Destroy();
	}
	m_edits.erase(m_edits.begin() + from, m_edits.begin() + to);
	if (m_indexOfNextAdd > to)
	{
		m_indexOfNextAdd -= (to - from);
	}
	else if (m_indexOfNextAdd >= from)
	{
		m_indexOfNextAdd = from;
	}
}

void CUndoManager::DestroyImpl() throw()
{
	m_indexOfNextAdd = 0;
	CCompoundEdit::DestroyImpl();
}

void CUndoManager::SetExecuted(bool executed)
{
	if (!m_inProgress)
	{
		CCompoundEdit::SetExecuted(executed);
	}
}

bool CUndoManager::AddEditImpl(const IUndoableEditPtr& edit)
{
	if (m_indexOfNextAdd < m_edits.size())
	{
		m_edits.resize(m_indexOfNextAdd);
	}

	auto addResult = CCompoundEdit::AddEditImpl(edit);

	m_indexOfNextAdd = m_edits.size();

	if (m_edits.size() > MAX_EDITS)
	{
		TrimEdits(0, m_edits.size() - MAX_EDITS);
	}

	return addResult;
}

void CUndoManager::UndoImpl()
{
	if (m_inProgress)
	{
		auto edit = GetEditToBeUndone();

		if (edit != nullptr)
		{
			UndoTo(edit);
		}
	}
	else
	{
		CCompoundEdit::UndoImpl();
	}
}

void CUndoManager::RedoImpl()
{
	if (m_inProgress)
	{
		auto edit = GetEditToBeRedone();
		if (edit != nullptr)
		{
			RedoTo(edit);
		}
	}
	else
	{
		CCompoundEdit::RedoImpl();
	}
}

void CUndoManager::EndImpl()
{
	TrimEdits(m_indexOfNextAdd, m_edits.size());
}