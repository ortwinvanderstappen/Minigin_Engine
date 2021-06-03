#include "MiniginPCH.h"
#include "SuicideCommand.h"
#include "GameObject.h"

minigen::SuicideCommand::SuicideCommand(std::shared_ptr<minigen::GameObject> gameObject) :
	m_ObjectToKill{ gameObject }
{}

bool minigen::SuicideCommand::Execute()
{
	if(m_ObjectToKill != nullptr)
	{
		
	}

	return true;
}
