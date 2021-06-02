#pragma once
#include "Observer.h"
#include <memory>
#include <vector>

#include "ComponentHolder.h"

namespace minigen
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Initialize(){};

		void Notify(const GameObject& gameObject, Observer::Event event);
		void AddObserver(std::shared_ptr<Observer> pObserver);
		void RemoveObserver(std::shared_ptr<Observer> pObserver);

		void SetParent(GameObject* pParentObject);
	protected:
		Component();
		virtual ~Component();

		GameObject* m_pParentObject;
	private:
		std::vector<std::shared_ptr<Observer>> m_spObservers{};
	};
}
