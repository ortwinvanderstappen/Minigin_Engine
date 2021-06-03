#include "MiniginPCH.h"
#include "Scene.h"
#include "CollisionSubject.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Script.h"
#include <algorithm>

using namespace minigen;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name)
{}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->SetParentScene(this);
}

void Scene::Update()
{
	for (auto& object : m_Objects)
	{
		object->Update();
	}

	// Collision pass
	for (auto& object : m_Objects)
	{
		std::shared_ptr<CollisionSubject> collisionSubject = object->GetCollisionSubject();
		if (collisionSubject)
		{
			for (auto& otherObject : m_Objects)
			{
				if (object == otherObject) continue;

				std::shared_ptr<CollisionSubject> otherCollisionSubject = otherObject->GetCollisionSubject();
				if (otherCollisionSubject)
				{
					collisionSubject->HandleCollision(otherCollisionSubject);
				}
			}
		}
	}

	// Remove objects that are marked for delete
	m_Objects.erase(std::remove_if(m_Objects.begin(), m_Objects.end(), 
		[](std::shared_ptr<GameObject> spObject)
		{
			return spObject->IsMarkedForDelete();
		}
	), m_Objects.end());
}

void Scene::Render() const
{
	const Color3f debugDrawColor{ 1.f, 0.f, 0.f };

	for (const auto& object : m_Objects)
	{
		// Render all render components
		for (const std::shared_ptr<Component> spComponent : object->GetComponents())
		{
			std::shared_ptr<RenderComponent> spRenderComponent = std::dynamic_pointer_cast<RenderComponent>(spComponent);
			if (spRenderComponent) spRenderComponent->Render();
		}

		// Render all the scripts and it's components
		for (const std::shared_ptr<Script> spScript : object->GetScripts())
		{
			spScript->Render();
		}

		// Collision render pass (debug only)
#ifdef _DEBUG
		std::shared_ptr<CollisionSubject> col = object->GetCollisionSubject();
		if (col)
		{
			const Rectf& collisionBounds = col->GetCollisionBounds();
			Renderer::GetInstance().RenderRect(collisionBounds, debugDrawColor);
		}
#endif

	}
}

const std::string& Scene::GetName()
{
	return m_Name;
}

