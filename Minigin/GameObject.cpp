#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Script.h"


void minigen::GameObject::AddComponent(std::shared_ptr<Component> spComponent)
{
	ComponentHolder::AddComponent(spComponent);
	spComponent->SetParent(this);
	spComponent->Initialize();
}

void minigen::GameObject::AddScript(std::shared_ptr<Script> spScript)
{
	m_Scripts.push_back(spScript);
	spScript->SetParent(this);
	spScript->Initialize();
}

const std::vector<std::shared_ptr<minigen::Script>>& minigen::GameObject::GetScripts() const
{
	return m_Scripts;
}

void minigen::GameObject::SetParentScene(Scene* pScene)
{
	m_pParentScene = pScene;
}

minigen::Scene* minigen::GameObject::GetScene() const
{
	return m_pParentScene;
}

const glm::vec3& minigen::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

void minigen::GameObject::Update()
{
	// Update all the components of this game object
	for (std::shared_ptr<Component> component : m_spComponents)
	{
		component->Update();
	}

	// Update all the scripts and it's components
	for (std::shared_ptr<Script> script : m_Scripts)
	{
		script->Update();
	}
}

void minigen::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
