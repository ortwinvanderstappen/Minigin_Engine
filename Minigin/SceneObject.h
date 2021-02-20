#pragma once
#include <glm/detail/type_vec.hpp>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;

		template <typename T>
		std::shared_ptr<T> GetComponent() const;
		void AddComponent(std::shared_ptr<Component> spComponent);
		const std::vector<std::shared_ptr<Component>>& GetComponents() const;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

		const glm::vec3& GetPosition() const;

	protected:
		Transform m_Transform;
		std::vector<std::shared_ptr<Component>> m_spComponents{};
	};

	inline void dae::SceneObject::AddComponent(std::shared_ptr<Component> spComponent)
	{
		m_spComponents.push_back(spComponent);
	}

	inline const std::vector<std::shared_ptr<Component>>& dae::SceneObject::GetComponents() const
	{
		return m_spComponents;
	}

	inline const glm::vec3& SceneObject::GetPosition() const
	{
		return m_Transform.GetPosition();
	}

	template <typename T>
	std::shared_ptr<T> SceneObject::GetComponent() const
	{
		for (auto& component : m_spComponents)
		{
			if (typeid(component).name() == typeid(T).name())
			{
				return component;
			}
		}

		// No component found
		return nullptr;
	}
}
