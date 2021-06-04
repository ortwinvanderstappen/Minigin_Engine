#include "MiniginPCH.h"
#include "GameObject.h"
#include "RenderComponent.h"

minigen::GameObject::GameObject() :
	m_pParentScene(nullptr),
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

void minigen::GameObject::SetCollisionSubject(std::shared_ptr<CollisionSubject> spCollisionSubject)
{
	m_spCollisionSubject = spCollisionSubject;
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

const Point2f& minigen::GameObject::GetPosition() const
{
	return m_Transform.GetPosition();
}

void minigen::GameObject::Update()
{
	// Update all the components of this game object
	for (int i = 0; i < m_spComponents.size(); ++i)
	{
		m_spComponents[i]->Update();
	}
}

void minigen::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}

void minigen::GameObject::SetPosition(const Point2f& pos)
{
	m_Transform.SetPosition(pos.x, pos.y);
}
