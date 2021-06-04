#include "MiniginPCH.h"
#include "MenuComponent.h"

void minigen::MenuComponent::AddButton(std::shared_ptr<ButtonComponent> spButton)
{
	m_wpButtons.push_back(spButton);
}
