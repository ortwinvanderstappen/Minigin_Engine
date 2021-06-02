#pragma once
#include "Singleton.h"

class Observer;
class Subject : public minigen::Singleton<Subject>
{
public:
	void AddObserver(std::shared_ptr<Observer> spObserver);
private:
	friend class Singleton<Subject>;
	Subject() = default;

	std::vector<std::shared_ptr<Observer>> m_Observers;
};

