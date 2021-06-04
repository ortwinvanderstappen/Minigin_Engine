#pragma once
#include "ComponentHolder.h"

namespace minigen {
	class GameObject;

	class Script
	{
	public:
		Script() = default;
		virtual ~Script() = default;

		virtual void Initialize() {};
		virtual void Update() {};
		virtual void Render() const {};

		// Collision
		virtual void OnCollisionEnter(GameObject* const) {};

		//void AddComponent(std::shared_ptr<Component> spComponent) override;

		void SetParent(GameObject* pGameObject);
		GameObject* GetParent() const;

	protected:
		GameObject* m_pParentObject = nullptr;
	};
}

