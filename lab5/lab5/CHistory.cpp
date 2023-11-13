#include "CHistory.h"

using namespace std;

constexpr int MAX_HISTORY_SIZE = 10;

bool CHistory::CanUndo() const
{
	return m_currentCommandIndex != 0;
}

bool CHistory::CanRedo() const
{
	return m_currentCommandIndex != m_commands.size();
}

void CHistory::Undo()
{
	if (CanUndo())
	{
		m_commands[m_currentCommandIndex - 1]->Unexecute();
		--m_currentCommandIndex;
	}
}

void CHistory::Redo()
{
	if (CanRedo())
	{
		m_commands[m_currentCommandIndex + 1]->Execute(); // without + 1
		++m_currentCommandIndex;
	}
}

void CHistory::AddAndExecuteCommand(unique_ptr<ICommand>&& command)
{
	if (m_currentCommandIndex < m_commands.size())
	{
		command->Execute();
		++m_currentCommandIndex;
		m_commands.resize(m_currentCommandIndex);
		// m_commands.back() = move(command);
		m_commands.emplace_back(move(command));
		return;
	}

	m_commands.emplace_back(nullptr);
	command->Execute();

	m_commands.back() = move(command);
	++m_currentCommandIndex;
	if (m_currentCommandIndex > MAX_HISTORY_SIZE)
	{
		m_commands.pop_front();
		--m_currentCommandIndex;
	}
}