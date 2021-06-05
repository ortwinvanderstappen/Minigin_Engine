#pragma once
#include "GameObject.h"
#include "Singleton.h"

namespace minigen {
	class Observer;
	class Subject
	{
	public:
		Subject();
		
		void AddObserver(std::shared_ptr<Observer> spObserver);
		void Notify(GameObject* pGameObject, Observer::Event event);
	
	protected:
		std::vector<std::shared_ptr<Observer>> m_Observers;
	};
}

