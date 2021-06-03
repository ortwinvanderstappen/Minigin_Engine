#include "MiniginPCH.h"
#include "Script.h"

#include "RenderComponent.h"

void minigen::Script::Update()
{
	for (std::shared_ptr<Component> component : GetComponents())
	{
		component->Update();
	}
}

void minigen::Script::Render() const
{
	for (std::shared_ptr<Component> spComponent : GetComponents())
	{
		std::shared_ptr<RenderComponent> spRenderComponent = std::dynamic_pointer_cast<RenderComponent>(spComponent);
		if (spRenderComponent) spRenderComponent->Render();
	}
}

void minigen::Script::AddComponent(std::shared_ptr<Component> spComponent)
{
	ComponentHolder::AddComponent(spComponent);
	spComponent->SetParent(m_pParentObject);
	spComponent->Initialize();
}

void minigen::Script::SetParent(GameObject* pGameObject)
{
	m_pParentObject = pGameObject;
}

minigen::GameObject* minigen::Script::GetParent() const
{
	return m_pParentObject;
}
