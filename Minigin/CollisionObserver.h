#pragma once
#include "Observer.h"

namespace minigen {
	class Component;

	class CollisionObserver :public Observer
	{
	public:
		CollisionObserver(Component* pComponent);
		
		void Notify(GameObject* pGameObject, Event event) override;

	private:
		Component* m_pComponent;
	};
}

