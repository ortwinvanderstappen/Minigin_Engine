#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

minigen::Subject::Subject() :
	m_Observers()
{}

void minigen::Subject::AddObserver(std::shared_ptr<Observer> spObserver)
{
	m_Observers.push_back(spObserver);
}

void minigen::Subject::Notify(GameObject* pGameObject, Observer::Event event)
{
	for (std::shared_ptr<Observer> spObserver : m_Observers)
	{
		spObserver->Notify(pGameObject, event);
	}
}
