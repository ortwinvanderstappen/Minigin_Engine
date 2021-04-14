#pragma once
#include "Component.h"
#include "InputManager.h"

class InputComponent final: public Component
{
public:
	void Update() override;
	void AddInput(const minigen::InputManager::KeyInput& input);
private:
	std::vector<minigen::InputManager::KeyInput> m_InputMap;
};

