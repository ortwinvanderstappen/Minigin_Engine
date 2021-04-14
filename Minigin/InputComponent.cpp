#include "MiniginPCH.h"
#include "InputComponent.h"

void InputComponent::Update()
{
	// Check if any inputs have been pressed and let the inputManager handle them
	minigen::InputManager::GetInstance().HandleInputStates(m_InputMap);
}

void InputComponent::AddInput(const minigen::InputManager::KeyInput& input)
{
	m_InputMap.push_back(input);
}
