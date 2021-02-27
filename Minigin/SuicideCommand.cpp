#include "MiniginPCH.h"
#include "SuicideCommand.h"

#include <iostream>


#include "GameObject.h"
#include "HealthComponent.h"

dae::SuicideCommand::SuicideCommand(std::shared_ptr<dae::GameObject> gameObject) :
	m_ObjectToKill{ gameObject }
{}

void dae::SuicideCommand::Execute()
{
	if(m_ObjectToKill != nullptr)
	{
		std::shared_ptr<HealthComponent> hc = m_ObjectToKill->GetComponent<HealthComponent>();

		if(hc != nullptr)
		{
			hc->SetHealth(0);
		}
	}
}
