#pragma once
#include "Component.h"
#include "InputManager.h"

namespace minigen {
	class InputComponent final : public Component
	{
	public:
		void Update() override;
		void AddInput(const InputManager::KeyInput& input);
	private:
		std::vector<InputManager::KeyInput> m_InputMap;
	};
}

