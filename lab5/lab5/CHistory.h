#pragma once
#include <deque>
#include "ICommandExecuter.h"

class CHistory : public ICommandExecuter
{
public:
	void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command) override;
	void Undo();
	void Redo();
	bool CanUndo() const;
	bool CanRedo() const;

private:
	std::deque<std::unique_ptr<ICommand>> m_commands;
	size_t m_currentCommandIndex = 0;
};