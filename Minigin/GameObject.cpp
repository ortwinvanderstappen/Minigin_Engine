#include "MiniginPCH.h"
#include "GameObject.h"

#include "ButtonComponent.h"
#include "InputManager.h"
#include "MouseObserver.h"
#include "Subject.h"

minigen::GameObject::GameObject() :
	m_pParentScene(nullptr),
	m_IsMarkedForDelete(false),
	m_IsMarkedForLateDelete(false),
	m_Tag("GameObject")
{}

minigen::GameObject::~GameObject()
{
}

void minigen::GameObject::MarkForDelete()
{
	m_IsMarkedForDelete = true;
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

	// Assign buttons to a mouse observer
	const std::shared_ptr<ButtonComponent> buttonComponent = std::dynamic_pointer_cast<ButtonComponent>(spComponent);
	if (buttonComponent)
	{
		const std::shared_ptr<MouseObserver> spMouseObserver = std::make_shared<MouseObserver>(buttonComponent);
		InputManager::GetInstance().GetMouseSubject()->AddObserver(spMouseObserver);
	}
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
	for (size_t i = 0; i < m_spComponents.size(); ++i)
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
