#pragma once
#include "Observer.h"

namespace minigen {
	class Script;

	class CollisionObserver :public Observer
	{
	public:
		CollisionObserver(Script* pScript);
		
		void Notify(GameObject* pGameObject, Event event) override;

	private:
		Script* m_pScript;
	};
}

