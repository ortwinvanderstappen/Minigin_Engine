#include "MiniginPCH.h"
#include "CollisionObserver.h"

#include "Script.h"

minigen::CollisionObserver::CollisionObserver(Script* pScript) :
	m_pScript(pScript)
{}

void minigen::CollisionObserver::Notify(GameObject* pOther, Event event)
{
	switch (event)
	{
	case Event::event_collision:
		m_pScript->OnCollisionEnter(pOther);
		break;
	default:;
	}
}
