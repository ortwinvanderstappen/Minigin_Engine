#include "MiniginPCH.h"
#include "SuicideCommand.h"

#include <iostream>


#include "GameObject.h"
#include "HealthComponent.h"

minigen::SuicideCommand::SuicideCommand(std::shared_ptr<minigen::GameObject> gameObject) :
	m_ObjectToKill{ gameObject }
{}

bool minigen::SuicideCommand::Execute()
{
	if(m_ObjectToKill != nullptr)
	{
		std::shared_ptr<HealthComponent> hc = m_ObjectToKill->GetComponent<HealthComponent>();

		if(hc != nullptr)
		{
			hc->SetHealth(0);
		}
	}

	return true;
}
