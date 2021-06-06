#include "stdafx.h"
#include "PlayerControllerComponent.h"

#include <GameObject.h>
#include <InputComponent.h>
#include <InputManager.h>
#include <iostream>

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
		std::cerr << "PlayerControllerComponent: Required component in child: TileMovementComponent not found!\n";
	}

	const std::shared_ptr<minigen::InputComponent> spInputComponent = std::make_shared<minigen::InputComponent>();
	m_pParentObject->AddComponent(spInputComponent);

	switch (m_HardwareType)
	{
	case HardwareType::Keyboard:
		CreateKeyboardInputs(spInputComponent);
		break;
	case HardwareType::Controller:
		CreateControllerInputs(spInputComponent);
		break;
	case HardwareType::Both:
		CreateKeyboardInputs(spInputComponent);
		CreateControllerInputs(spInputComponent);
		break;
	default:;
	}
}

void PlayerControllerComponent::Update()
{
	switch (m_HardwareType)
	{
	case HardwareType::Keyboard:
		CheckKeyboardInputs();
		break;
	case HardwareType::Controller:
		CheckControllerInputs();
		break;
	case HardwareType::Both:
		CheckKeyboardInputs();
		CheckControllerInputs();
		break;
	default:;
	}
}

void PlayerControllerComponent::CreateKeyboardInputs(const std::shared_ptr<minigen::InputComponent>& spInputComponent)
{
	minigen::InputManager::KeyInput upInput{};
	upInput.id = static_cast<int>(InputId::up);
	upInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	upInput.inputType = minigen::InputManager::InputType::onKeyDown;
	upInput.inputButton.keyboardButton = SDLK_w;
	spInputComponent->AddInput(upInput);

	minigen::InputManager::KeyInput rightInput{};
	rightInput.id = static_cast<int>(InputId::right);
	rightInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	rightInput.inputType = minigen::InputManager::InputType::onKeyDown;
	rightInput.inputButton.keyboardButton = SDLK_d;
	spInputComponent->AddInput(rightInput);

	minigen::InputManager::KeyInput downInput{};
	downInput.id = static_cast<int>(InputId::down);
	downInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	downInput.inputType = minigen::InputManager::InputType::onKeyDown;
	downInput.inputButton.keyboardButton = SDLK_s;
	spInputComponent->AddInput(downInput);

	minigen::InputManager::KeyInput leftInput{};
	leftInput.id = static_cast<int>(InputId::left);
	leftInput.hardwareType = minigen::InputManager::HardwareType::keyboard;
	leftInput.inputType = minigen::InputManager::InputType::onKeyDown;
	leftInput.inputButton.keyboardButton = SDLK_a;
	spInputComponent->AddInput(leftInput);

}

void PlayerControllerComponent::CreateControllerInputs(const std::shared_ptr<minigen::InputComponent>& spInputComponent)
{
	const int inputOffset = 4;

	minigen::InputManager::KeyInput upInput{};
	upInput.id = static_cast<int>(InputId::up) + inputOffset;
	upInput.hardwareType = minigen::InputManager::HardwareType::controller;
	upInput.inputType = minigen::InputManager::InputType::onKeyDown;
	upInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonUp;
	spInputComponent->AddInput(upInput);

	minigen::InputManager::KeyInput rightInput{};
	rightInput.id = static_cast<int>(InputId::right) + inputOffset;
	rightInput.hardwareType = minigen::InputManager::HardwareType::controller;
	rightInput.inputType = minigen::InputManager::InputType::onKeyDown;
	rightInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonRight;
	spInputComponent->AddInput(rightInput);

	minigen::InputManager::KeyInput downInput{};
	downInput.id = static_cast<int>(InputId::down) + inputOffset;
	downInput.hardwareType = minigen::InputManager::HardwareType::controller;
	downInput.inputType = minigen::InputManager::InputType::onKeyDown;
	downInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonDown;
	spInputComponent->AddInput(downInput);

	minigen::InputManager::KeyInput leftInput{};
	leftInput.id = static_cast<int>(InputId::left) + inputOffset;
	leftInput.hardwareType = minigen::InputManager::HardwareType::controller;
	leftInput.inputType = minigen::InputManager::InputType::onKeyDown;
	leftInput.inputButton.controllerButton = minigen::InputManager::ControllerButton::ButtonLeft;
	spInputComponent->AddInput(leftInput);
}

void PlayerControllerComponent::CheckKeyboardInputs() const
{
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::up)))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::up);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::right)))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::right);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::down)))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::down);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::left)))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::left);
}

void PlayerControllerComponent::CheckControllerInputs() const
{
	const int offset = 4;
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::up) + offset))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::up);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::right) + offset))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::right);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::down) + offset))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::down);
	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::left) + offset))
		m_spTileMovementComponent->Move(TileMovementComponent::MovementType::left);
}
