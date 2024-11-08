#pragma once
#include <memory>
#include <string>

class IUndoableEdit
{
public:
	virtual ~IUndoableEdit() = default;

	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual void Destroy() = 0;

	virtual bool AddEdit(const IUndoableEditPtr& edit) = 0;
	virtual bool ReplaceEdit(const IUndoableEditPtr& edit) = 0;

	virtual std::string GetName() const = 0;
};

using IUndoableEditPtr = std::shared_ptr<IUndoableEdit>;