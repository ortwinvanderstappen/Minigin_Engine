#include "MiniginPCH.h"
#include "Component.h"

#include "GameObject.h"


Component::Component()
{}

Component::~Component()
{}

void Component::Notify(const minigen::GameObject& gameObject, Observer::Event event)
{
	for (std::shared_ptr<Observer>& observer : m_spObservers)
	{
		observer->Notify(gameObject, event);
	}
}

void Component::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_spObservers.push_back(pObserver);
}

void Component::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	m_spObservers.erase(std::remove(m_spObservers.begin(), m_spObservers.end(), pObserver), m_spObservers.end());
}

void Component::SetParent(minigen::GameObject* pParentObject)
{
	m_pParentObject = pParentObject;
}
