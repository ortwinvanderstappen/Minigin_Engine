#include "MiniginPCH.h"
#include "CollisionObserver.h"
#include "Component.h"

minigen::CollisionObserver::CollisionObserver(Component* pComponent) :
	m_pComponent(pComponent)
{
}

void minigen::CollisionObserver::Notify(GameObject* pOther, Event event)
{
	switch (event)
	{
	case Event::event_collision:
		m_pComponent->OnCollisionEnter(pOther);
		break;
	default:;
	}
}
