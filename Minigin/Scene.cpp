#include "MiniginPCH.h"
#include "Scene.h"
#include "CollisionSubject.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include <algorithm>

using namespace minigen;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) :
	m_Name(name),
	m_DrawDebugColliders(true)
{}

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	object->SetParentScene(this);
}

void Scene::Update()
{
	const size_t objects = m_Objects.size();
	
	for (int i = 0; i < objects; ++i)
	{
		m_Objects[i]->Update();
	}

	// Collision pass
	for (int i = 0; i < objects; ++i)
	{
		const std::shared_ptr<GameObject>& object = m_Objects[i];
		if (object->IsMarkedForDelete()) continue;

		std::shared_ptr<CollisionSubject> collisionSubject = object->GetCollisionSubject();
		if (collisionSubject)
		{
			for (int j = 0; j < objects; ++j)
			{
				const std::shared_ptr<GameObject>& otherObject = m_Objects[j];
				if (object == otherObject || otherObject->IsMarkedForDelete()) continue;

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
			if (spObject->IsMarkedForDelete() || spObject->IsMarkedForLateDelete())
				std::cout << "Deleting object with tag: " << spObject->GetTag() << "\n";

			return spObject->IsMarkedForDelete() || spObject->IsMarkedForLateDelete();
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

		// Collision render pass (debug only)
#ifdef _DEBUG
		if (m_DrawDebugColliders)
		{
			std::shared_ptr<CollisionSubject> col = object->GetCollisionSubject();
			if (col)
			{
				const Rectf& collisionBounds = col->GetCollisionBounds();
				Renderer::GetInstance().RenderRect(collisionBounds, debugDrawColor);
			}
		}
#endif
	}
}

const std::string& Scene::GetName()
{
	return m_Name;
}

