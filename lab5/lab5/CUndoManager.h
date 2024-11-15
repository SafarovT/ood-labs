#pragma once
#include <functional>
#include "CCompoundEdit.h"

class CUndoManager : public CCompoundEdit
{
public:

	bool CanUndo() const final;
	bool CanRedo() const final;

	size_t GetCurrentEditIndex() const;

	void Clear();

private:
	bool AddEditImpl(const IUndoableEditPtr& edit) final;
	void UndoImpl() final;
	void RedoImpl() final;
	void EndImpl() final;
	void SetExecuted(bool executed) final;
	void DestroyImpl() throw() final;

	IUndoableEditPtr GetEditToBeUndone() const;
	IUndoableEditPtr GetEditToBeRedone() const;
	void UndoTo(const IUndoableEditPtr& edit);
	void RedoTo(const IUndoableEditPtr& edit);
	void TrimEdits(size_t from, size_t to);

	const size_t MAX_EDITS = 10;
	size_t m_indexOfNextAdd = 0;
};

using AddCommandFunction = std::function<void(const IUndoableEditPtr&)>;
