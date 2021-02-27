#pragma once
#include "Observer.h"

namespace dae {
	class GameObject;
}

class Component
{
public:
	virtual void Update() = 0;

	void Notify(const dae::GameObject& gameObject, Observer::Event event);
	void AddObserver(std::shared_ptr<Observer> pObserver);
	void RemoveObserver(std::shared_ptr<Observer> pObserver);

	void SetParent(dae::GameObject* pParentObject);
protected:
	Component();
	virtual ~Component();
	
	dae::GameObject* m_pParentObject = nullptr;
private:
	std::vector<std::shared_ptr<Observer>> m_spObservers{};
};
