#include "MiniginPCH.h"
#include "CollisionSubject.h"


#include "CollisionObserver.h"
#include "GameObject.h"

minigen::CollisionSubject::CollisionSubject(GameObject* pParentObject, const Rectf& boundaries) :
	m_pParentObject(pParentObject),
	m_Boundaries(boundaries)
{}

Rectf minigen::CollisionSubject::GetCollisionBounds() const
{
	const glm::vec3& parentPos = m_pParentObject->GetPosition();
	return Rectf{ m_Boundaries.x + parentPos.x, m_Boundaries.y + parentPos.y, m_Boundaries.w, m_Boundaries.h };
}

void minigen::CollisionSubject::HandleCollision(std::shared_ptr<CollisionSubject> spOtherCollider)
{
	const Rectf& otherBounds = spOtherCollider->GetCollisionBounds();
	const Rectf& bounds = GetCollisionBounds();

	if (bounds.x < otherBounds.x + otherBounds.w && bounds.x + bounds.w > otherBounds.x
		&& bounds.y < otherBounds.y + otherBounds.h && bounds.y + bounds.h > otherBounds.y)
	{
		Notify(spOtherCollider->GetParentObject(), Observer::Event::event_collision);
	}
}

minigen::GameObject* minigen::CollisionSubject::GetParentObject() const
{
	return m_pParentObject;
}
