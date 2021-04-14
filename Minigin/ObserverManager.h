#pragma once
#include "Singleton.h"

class Observer;

class ObserverManager : public minigen::Singleton<ObserverManager>
{
public:
	void AddObserver(std::shared_ptr<Observer> spObserver);
private:
	friend class Singleton<ObserverManager>;
	ObserverManager() = default;

	std::vector<std::shared_ptr<Observer>> m_Observers;
};

