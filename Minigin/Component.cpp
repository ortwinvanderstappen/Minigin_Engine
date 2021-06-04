#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

minigen::Component::Component() :
	m_pParentObject(nullptr)
{}

minigen::Component::~Component()
{}

void minigen::Component::SetParent(GameObject* pParentObject)
{
	m_pParentObject = pParentObject;
}

minigen::GameObject* minigen::Component::GetParent() const
{
	return m_pParentObject;
}
