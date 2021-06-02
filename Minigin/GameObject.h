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
	class GameObject final: public ComponentHolder
	{
	public:
		void Update();
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddComponent(std::shared_ptr<Component> spComponent) override;
		
		const glm::vec3& GetPosition() const;

	private:
		Transform m_Transform;
	};
}
