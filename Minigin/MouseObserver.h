#pragma once
#include "Observer.h"

namespace minigen {
	class ButtonComponent;

	class MouseObserver : public Observer
	{
	public:
		MouseObserver(std::shared_ptr<ButtonComponent> spButton);
		void Notify(GameObject* pGameObject, Event event) override;

	private:
		std::weak_ptr<ButtonComponent> m_wpButton;
	};
}

