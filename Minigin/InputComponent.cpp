#include "MiniginPCH.h"
#include "InputComponent.h"

void minigen::InputComponent::Update()
{
	// Check if any inputs have been pressed and let the inputManager handle them
	InputManager::GetInstance().HandleInputStates(m_InputMap);

	std::cout << "updating input...\n";
}

void minigen::InputComponent::AddInput(const InputManager::KeyInput& input)
{
	m_InputMap.push_back(input);
}
