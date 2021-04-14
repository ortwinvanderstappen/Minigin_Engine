#pragma once
#include "Observer.h"

namespace minigen {
	class GameObject;
}

class Component
{
public:
	virtual void Update() = 0;

	void Notify(const minigen::GameObject& gameObject, Observer::Event event);
	void AddObserver(std::shared_ptr<Observer> pObserver);
	void RemoveObserver(std::shared_ptr<Observer> pObserver);

	void SetParent(minigen::GameObject* pParentObject);
protected:
	Component();
	virtual ~Component();
	
	minigen::GameObject* m_pParentObject = nullptr;
private:
	std::vector<std::shared_ptr<Observer>> m_spObservers{};
};
