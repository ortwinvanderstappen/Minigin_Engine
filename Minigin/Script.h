#pragma once
#include "ComponentHolder.h"

namespace minigen {
	class GameObject;

	class Script : public ComponentHolder
	{
	public:
		Script() = default;
		~Script() = default;

		virtual void Initialize() {};
		virtual void Update();
		virtual void Render() const;

		// Collision
		virtual void OnCollisionEnter(GameObject* const){};

		void AddComponent(std::shared_ptr<Component> spComponent) override;
		void SetParent(GameObject* pGameObject);

	protected:
		GameObject* m_pParentObject = nullptr;
	};
}

