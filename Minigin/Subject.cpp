#include "MiniginPCH.h"
#include "Subject.h"

void Subject::AddObserver(std::shared_ptr<Observer> spObserver)
{
	m_Observers.push_back(spObserver);
}
