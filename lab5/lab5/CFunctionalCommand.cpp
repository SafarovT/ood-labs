#include "CFunctionalCommand.h"

using namespace std;

void CFunctionalCommand::DoExecute()
{
	m_doExecute();
}

void CFunctionalCommand::DoUnexecute()
{
	m_doUnexecute();
}