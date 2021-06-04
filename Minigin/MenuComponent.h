#pragma once
#include "Component.h"

namespace minigen {
	class ButtonComponent;

	class MenuComponent : public Component
	{
	public:
		MenuComponent() = default;

		void AddButton(std::shared_ptr<ButtonComponent> spButton);
	private:
		std::vector<std::weak_ptr<ButtonComponent>> m_wpButtons;
	};
}
