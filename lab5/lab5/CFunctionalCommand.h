#pragma once
#include <functional>
#include "CAbstractCommand.h"

class CFunctionalCommand : public CAbstractCommand
{
public:
	CFunctionalCommand(std::function<void()> doExecute, std::function<void()> doUnexecute)
		: m_doUnexecute(doExecute)
		, m_doExecute(doUnexecute)
	{}

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::function<void()> m_doExecute;
	std::function<void()> m_doUnexecute;
};

