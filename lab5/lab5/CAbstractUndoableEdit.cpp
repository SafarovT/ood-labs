#include "CAbstractUndoableEdit.h"
#include <stdexcept>
#include <cassert>

using namespace std;

bool CAbstractUndoableEdit::CanUndo() const
{
	return IsExecuted() && m_isAlive;
}

bool CAbstractUndoableEdit::CanRedo() const
{
	return !IsExecuted() && m_isAlive;
}

void CAbstractUndoableEdit::Undo()
{
	if (!CanUndo())
	{
		throw logic_error("Can't undo");
	}
	SetExecuted(false);
	UndoImpl();
}

void CAbstractUndoableEdit::Redo()
{
	if (!CanRedo())
	{
		throw logic_error("Can't redo");
	}
	SetExecuted(true);
	RedoImpl();
}

void CAbstractUndoableEdit::Destroy() noexcept
{
	if (m_isAlive)
	{
		m_isAlive = false;
		DestroyImpl();
	}
}

bool CAbstractUndoableEdit::AddEdit(const IUndoableEditPtr& edit)
{
	assert(edit);
	if (!m_isAlive)
	{
		throw logic_error("UndoableEdit has been destroyed");
	}
	return AddEditImpl(edit);
}

bool CAbstractUndoableEdit::ReplaceEdit(const IUndoableEditPtr& edit)
{
	assert(edit);
	if (!m_isAlive)
	{
		throw logic_error("UndoableEdit has been destroyed");
	}
	if (m_canBeReplaced)
	{
		return ReplaceEditImpl(edit);
	}
	return false;
}

std::string CAbstractUndoableEdit::GetName() const
{
	assert(!m_name.empty());
	return m_name;
}

void CAbstractUndoableEdit::SetReplaceable(bool canBeReplaced)
{
	m_canBeReplaced = canBeReplaced;
}

void CAbstractUndoableEdit::UndoImpl()
{
}

void CAbstractUndoableEdit::RedoImpl()
{
}

void CAbstractUndoableEdit::DestroyImpl() noexcept
{
}

bool CAbstractUndoableEdit::AddEditImpl(const IUndoableEditPtr&)
{
	return false;
}

bool CAbstractUndoableEdit::ReplaceEditImpl(const IUndoableEditPtr&)
{
	return false;
}

bool CAbstractUndoableEdit::IsExecuted() const
{
	return m_executed;
}

void CAbstractUndoableEdit::SetExecuted(bool executed)
{
	m_executed = executed;
}

void CAbstractUndoableEdit::SetName(const std::string& name)
{
	m_name = name;
}