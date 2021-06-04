#pragma once
#include "Observer.h"
#include <memory>
#include <vector>

namespace minigen
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update() = 0;
		virtual void Initialize(){};
		
		// Collision
		virtual void OnCollisionEnter(GameObject* const) {};

		void SetParent(GameObject* pParentObject);
	GameObject* GetParent() const;
	protected:
		Component();
		virtual ~Component();

		GameObject* m_pParentObject;
	};
}
