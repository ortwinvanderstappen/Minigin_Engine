#pragma once
#include "structs.h"
#include "Subject.h"

namespace minigen {
	class CollisionSubject : public Subject
	{
	public:
		CollisionSubject(GameObject* pParentObject, const Rectf& boundaries);

		Rectf GetCollisionBounds() const;
		void HandleCollision(std::shared_ptr<CollisionSubject> spOtherCollider);
		GameObject* GetParentObject() const;

	private:
		Rectf m_Boundaries;
		GameObject* m_pParentObject;
	};
}

