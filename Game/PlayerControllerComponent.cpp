#include "PlayerControllerComponent.h"

#include <iostream>
#include "GameObject.h"
#include "InputComponent.h"
#include "InputManager.h"
#include "TileMovementComponent.h"

PlayerControllerComponent::PlayerControllerComponent(HardwareType hardwareType) :
	m_HardwareType(hardwareType),
	m_spTileMovementComponent(nullptr)
{}

void PlayerControllerComponent::Initialize()
{
	m_spTileMovementComponent = m_pParentObject->GetComponent<TileMovementComponent>();
	if (m_spTileMovementComponent == nullptr)
	{
		std::cerr << "CoilyAIComponent: Required component in Coily: TileMovementComponent not found!\n";
	}

	switch (m_HardwareType)
	{
	case HardwareType::Keyboard:
		CreateKeyboardInputs();
		break;
	case HardwareType::Controller:
		CreateControllerInputs();
		break;
	}
}

void PlayerControllerComponent::Update()
{
	const int inputOffset = m_HardwareType == HardwareType::Controller ? 4 : 0;

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::up)+ inputOffset) )
	{
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::up);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::right)+ inputOffset) )
	{
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::right);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::down)+ inputOffset) )
	{
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::down);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::left) + inputOffset))
	{
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::left);
	}
}

void PlayerControllerComponent::CreateKeyboardInputs() const
{
	auto inputComponent = std::make_shared<minigen::InputComponent>();

	minigen::InputManager::KeyInput upInput{};
	upInput.id = static_cast<int>(InputId::up);
	upInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	upInput.inputType = minigen::InputManager::InputType::onKeyDown;
	upInput.inputButton.keyboardButton = SDLK_w;
	inputComponent->AddInput(upInput);

	minigen::InputManager::KeyInput rightInput{};
	rightInput.id = static_cast<int>(InputId::right);
	rightInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	rightInput.inputType = minigen::InputManager::InputType::onKeyDown;
	rightInput.inputButton.keyboardButton = SDLK_d;
	inputComponent->AddInput(rightInput);

	minigen::InputManager::KeyInput downInput{};
	downInput.id = static_cast<int>(InputId::down);
	downInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	downInput.inputType = minigen::InputManager::InputType::onKeyDown;
	downInput.inputButton.keyboardButton = SDLK_s;
	inputComponent->AddInput(downInput);

	minigen::InputManager::KeyInput leftInput{};
	leftInput.id = static_cast<int>(InputId::left);
	leftInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	leftInput.inputType = minigen::InputManager::InputType::onKeyDown;
	leftInput.inputButton.keyboardButton = SDLK_a;
	inputComponent->AddInput(leftInput);

	m_pParentObject->AddComponent(inputComponent);
}

void PlayerControllerComponent::CreateControllerInputs() const
{
	auto inputComponent = std::make_shared<minigen::InputComponent>();

	const int inputOffset = 4;

	minigen::InputManager::KeyInput upInput{};
	upInput.id = static_cast<int>(InputId::up) + inputOffset;
	upInput.hardwareType = minigen::InputManager::HardwareType::controller;
	upInput.inputType = minigen::InputManager::InputType::onKeyDown;
	upInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonUp;
	inputComponent->AddInput(upInput);

	minigen::InputManager::KeyInput rightInput{};
	rightInput.id = static_cast<int>(InputId::right) + inputOffset;
	rightInput.hardwareType = minigen::InputManager::HardwareType::controller;
	rightInput.inputType = minigen::InputManager::InputType::onKeyDown;
	rightInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonRight;
	inputComponent->AddInput(rightInput);

	minigen::InputManager::KeyInput downInput{};
	downInput.id = static_cast<int>(InputId::down) + inputOffset;
	downInput.hardwareType = minigen::InputManager::HardwareType::controller;
	downInput.inputType = minigen::InputManager::InputType::onKeyDown;
	downInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonDown;
	inputComponent->AddInput(downInput);

	minigen::InputManager::KeyInput leftInput{};
	leftInput.id = static_cast<int>(InputId::left) + inputOffset;
	leftInput.hardwareType = minigen::InputManager::HardwareType::controller;
	leftInput.inputType = minigen::InputManager::InputType::onKeyDown;
	leftInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonLeft;
	inputComponent->AddInput(leftInput);

	m_pParentObject->AddComponent(inputComponent);
}
