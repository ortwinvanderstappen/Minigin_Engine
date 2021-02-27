#include "MiniginPCH.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::AddComponent(std::shared_ptr<Component> spComponent)
{
	m_spComponents.push_back(spComponent);
	spComponent->SetParent(this);
}

const std::vector<std::shared_ptr<Component>>& dae::GameObject::GetComponents() const
{
	return m_spComponents;
}

const glm::vec3& dae::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

void dae::GameObject::Update()
{
	// Update all the components of this game object
	for (std::shared_ptr<Component> component : m_spComponents)
	{
		component->Update();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
