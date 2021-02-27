#include "MiniginPCH.h"
#include "ObserverManager.h"

void ObserverManager::AddObserver(std::shared_ptr<Observer> spObserver)
{
	m_Observers.push_back(spObserver);
}
