#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

minigen::Component::Component() :
	m_pParentObject(nullptr)
{}

minigen::Component::~Component()
{}

void minigen::Component::Notify(const minigen::GameObject& gameObject, Observer::Event event)
{
	for (std::shared_ptr<Observer>& observer : m_spObservers)
	{
		observer->Notify(gameObject, event);
	}
}

void minigen::Component::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_spObservers.push_back(pObserver);
}

void minigen::Component::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	m_spObservers.erase(std::remove(m_spObservers.begin(), m_spObservers.end(), pObserver), m_spObservers.end());
}

void minigen::Component::SetParent(GameObject* pParentObject)
{
	m_pParentObject = pParentObject;
}
