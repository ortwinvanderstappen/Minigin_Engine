#include "MiniginPCH.h"
#include "CustomCommand.h"

CustomCommand::CustomCommand(CommandCallback callback) :
	m_Callback(callback)
{}

bool CustomCommand::Execute()
{
	if(m_Callback)
	{
		m_Callback();
		return true;
	}

	return false;
}
