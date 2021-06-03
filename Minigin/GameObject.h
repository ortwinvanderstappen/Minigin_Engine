#pragma once
#include "Component.h"

#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

#include "ComponentHolder.h"
#include "Transform.h"

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

		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void MarkForDelete();
		bool IsMarkedForDelete() const;
		
		void AddComponent(std::shared_ptr<Component> spComponent) override;
		void AddScript(std::shared_ptr<Script> spScript);
		void SetCollisionSubject(std::shared_ptr<CollisionSubject> spCollisionSubject);

		const std::vector<std::shared_ptr<Script>>& GetScripts() const;
		std::shared_ptr<CollisionSubject> GetCollisionSubject() const;

		void SetParentScene(Scene* pScene);
		Scene* GetScene() const;

		void SetTag(const std::string& tag);
		const std::string& GetTag() const;

		const glm::vec3& GetPosition() const;

	protected:
		Scene* m_pParentScene;

	private:
		Transform m_Transform;
		std::vector<std::shared_ptr<Script>> m_Scripts;
		std::shared_ptr<CollisionSubject> m_spCollisionSubject;
		std::string m_Tag;

		bool m_IsMarkedForDelete;
	};
}
