#pragma once
#include <optional>
#include <vector>
#include "CAbstractUndoableEdit.h"

class CCompoundEdit : public CAbstractUndoableEdit
{
public:
	explicit CCompoundEdit(const std::optional<std::string>& customName = std::nullopt);
	~CCompoundEdit();
	bool CanUndo() const override;
	bool CanRedo() const override;
	std::string GetName() const override;
	void End();
	size_t GetEditCount() const;
	IUndoableEditPtr GetEdit(size_t index) const;

protected:
	void DestroyImpl() noexcept override;
	void UndoImpl() override;
	void RedoImpl() override;
	bool AddEditImpl(const IUndoableEditPtr& edit) override;
	virtual void EndImpl();
	void SetName(const std::string& name) override;

	std::vector<IUndoableEditPtr> m_edits;
	bool m_inProgress = true;

private:
	bool m_hasCustomName = false;
};

using CompoundEditUniquePtr = std::unique_ptr<CCompoundEdit>;