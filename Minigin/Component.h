#pragma once
#include "Observer.h"
#include <memory>
#include <vector>

#include "ComponentHolder.h"

namespace minigen
{
	class GameObject;
	class Component : public ComponentHolder
	{
	public:
		virtual void Update() = 0;

		void Notify(const GameObject& gameObject, Observer::Event event);
		void AddObserver(std::shared_ptr<Observer> pObserver);
		void RemoveObserver(std::shared_ptr<Observer> pObserver);

		virtual void AddComponent(std::shared_ptr<Component> spComponent) override;

		void SetParent(GameObject* pParentObject);
	protected:
		Component();
		virtual ~Component();

		GameObject* m_pParentObject = nullptr;
	private:
		std::vector<std::shared_ptr<Observer>> m_spObservers{};
	};
}
