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

		void SetParent(GameObject* pParentObject);
	protected:
		Component();
		virtual ~Component();

		GameObject* m_pParentObject;
	};
}
