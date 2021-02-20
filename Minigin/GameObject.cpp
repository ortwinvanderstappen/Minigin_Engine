#include "MiniginPCH.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::FixedUpdate()
{
	// FixedUpdate all the components of this game object
	for (std::shared_ptr<Component> component : m_spComponents)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
