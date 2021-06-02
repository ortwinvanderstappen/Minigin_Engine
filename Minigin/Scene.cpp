#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace minigen;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name)
{
}

void Scene::Add(const std::shared_ptr<GameObject>&object)
{
	m_Objects.push_back(object);
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		// Render all render components
		for (std::shared_ptr<Component> spComponent : object->GetComponents())
		{
			std::shared_ptr<RenderComponent> spRenderComponent = std::dynamic_pointer_cast<RenderComponent>(spComponent);
			if (spRenderComponent) spRenderComponent->Render();
		}
	}
}

const std::string& Scene::GetName()
{
	return m_Name;
}

