#pragma once
#include "Component.h"

#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

#include "ComponentHolder.h"
#include "Transform.h"
#include "string"

namespace minigen
{
	class Scene;
	class Script;
	class CollisionSubject;

	class GameObject final : public ComponentHolder
	{
	public:
		void Update();
		void SetPosition(float x, float y);
		void SetPosition(const Point2f& pos);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		template <typename T>
		std::shared_ptr<T> GetScript() const;

		// Early deletion, no collision calls, will still be remove at the end of the frame
		void MarkForDelete();
		// Late deletion, still has collision calls, also gets deleted at the end of the frame
		void MarkForLateDelete();
		bool IsMarkedForDelete() const;
		bool IsMarkedForLateDelete() const;
		
		void AddComponent(std::shared_ptr<Component> spComponent) override;
		void AddScript(std::shared_ptr<Script> spScript);
		void SetCollisionSubject(std::shared_ptr<CollisionSubject> spCollisionSubject);

		const std::vector<std::shared_ptr<Script>>& GetScripts() const;
		std::shared_ptr<CollisionSubject> GetCollisionSubject() const;

		void SetParentScene(Scene* pScene);
		Scene* GetScene() const;

		void SetTag(const std::string& tag);
		const std::string& GetTag() const;

		const Point2f& GetPosition() const;

	protected:
		Scene* m_pParentScene;

	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<Script>> m_Scripts;
		std::shared_ptr<CollisionSubject> m_spCollisionSubject;
		std::string m_Tag;

		bool m_IsMarkedForDelete;
		bool m_IsMarkedForLateDelete;
	};

	template <typename T>
	std::shared_ptr<T> GameObject::GetScript() const
	{
		for (const std::shared_ptr<Script>& script : m_Scripts)
		{
			std::shared_ptr<T> castedScript = std::dynamic_pointer_cast<T>(script);

			if (castedScript)
				return castedScript;
		}

		// No component found
		return nullptr;
	}
}
