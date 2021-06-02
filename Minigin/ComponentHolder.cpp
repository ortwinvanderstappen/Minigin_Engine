#include "MiniginPCH.h"
#include "ComponentHolder.h"

void minigen::ComponentHolder::AddComponent(std::shared_ptr<Component> spComponent)
{
	m_spComponents.push_back(spComponent);
}

const std::vector<std::shared_ptr<minigen::Component>>& minigen::ComponentHolder::GetComponents() const
{
	return m_spComponents;
}