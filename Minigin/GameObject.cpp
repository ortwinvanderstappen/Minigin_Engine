#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Script.h"

minigen::GameObject::GameObject() :
	m_IsMarkedForDelete(false),
	m_IsMarkedForLateDelete(false),
	m_Tag("GameObject")
{}

minigen::GameObject::~GameObject()
{
	std::cout << "Gameobject with tag " << GetTag() << " destructing\n";
}

void minigen::GameObject::MarkForDelete()
{
	m_IsMarkedForDelete = true;
	std::cout << "Marking object with tag " << GetTag() << " for delete\n";
}

void minigen::GameObject::MarkForLateDelete()
{
	m_IsMarkedForLateDelete = true;
}

bool minigen::GameObject::IsMarkedForDelete() const
{
	return m_IsMarkedForDelete;
}

bool minigen::GameObject::IsMarkedForLateDelete() const
{
	return m_IsMarkedForLateDelete;
}

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

void minigen::GameObject::SetCollisionSubject(std::shared_ptr<CollisionSubject> spCollisionSubject)
{
	m_spCollisionSubject = spCollisionSubject;
}

const std::vector<std::shared_ptr<minigen::Script>>& minigen::GameObject::GetScripts() const
{
	return m_Scripts;
}

std::shared_ptr<minigen::CollisionSubject> minigen::GameObject::GetCollisionSubject() const
{
	return m_spCollisionSubject;
}

void minigen::GameObject::SetParentScene(Scene* pScene)
{
	m_pParentScene = pScene;
}

minigen::Scene* minigen::GameObject::GetScene() const
{
	return m_pParentScene;
}

void minigen::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

const std::string& minigen::GameObject::GetTag() const
{
	return m_Tag;
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