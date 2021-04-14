#pragma once
#include "Component.h"

#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

#include "Transform.h"

namespace minigen
{
	class GameObject final
	{
	public:
		void Update();
		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		std::shared_ptr<T> GetComponent() const;
		void AddComponent(std::shared_ptr<Component> spComponent);
		const std::vector<std::shared_ptr<Component>>& GetComponents() const;

		const glm::vec3& GetPosition() const;

	protected:
		std::vector<std::shared_ptr<Component>> m_spComponents{};

	private:
		Transform m_Transform;
	};
	
	template <typename T>
	std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (const std::shared_ptr<Component>& component : m_spComponents)
		{
			std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);
			
			if (castedComponent)
				return castedComponent;
		}

		// No component found
		return nullptr;
	}
}
