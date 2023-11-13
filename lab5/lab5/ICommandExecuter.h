#pragma once
#include <memory>
#include "ICommand.h"

class ICommandExecuter
{
public:
	~ICommandExecuter() = default;

	virtual void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command) = 0;
};