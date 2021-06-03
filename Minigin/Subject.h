#pragma once
#include "GameObject.h"
#include "Singleton.h"

namespace minigen {
	class Observer;
	class Subject : public Singleton<Subject>
	{
	public:
		Subject();
		
		void AddObserver(std::shared_ptr<Observer> spObserver);

	protected:
		void Notify(GameObject* pGameObject, Observer::Event event);
		std::vector<std::shared_ptr<Observer>> m_Observers;

	private:
		friend class Singleton<Subject>;
	};
}

