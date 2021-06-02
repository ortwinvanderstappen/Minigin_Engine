#include "QBert.h"
#include <iostream>
#include "ImageRenderComponent.h"
#include "InputComponent.h"
#include "ArenaTile.h"
#include "GameArena.h"
#include "GameObject.h"

QBert::QBert(int playerIndex) :
	m_QbertImagePath("images/QBert.png"),
	m_PlayerIndex(playerIndex),
	m_pCurrentTile(nullptr)
{}

void QBert::Update()
{
	Script::Update();

	ProcessInput();

	if (m_pCurrentTile)
	{
		m_pCurrentTile->Activate();

		const Point2f& tileCenter = m_pCurrentTile->GetCenter();
		m_pParentObject->SetPosition(tileCenter.x, tileCenter.y);
	}
}

void QBert::Initialize()
{
	InitializeSprite();
	InitializeControls();
}

void QBert::InitializeSprite()
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float scale = 2.f;
	imageRenderComponent->AddImage(m_QbertImagePath, { -8 * scale,-16 * scale }, scale);
	AddComponent(imageRenderComponent);
}

void QBert::InitializeControls()
{
	if (m_PlayerIndex == 0)
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

		AddComponent(inputComponent);
	}
	else
	{

	}
}

void QBert::ProcessInput()
{
	if (!m_pCurrentTile) return;

	GameArena* pArena = m_pCurrentTile->GetArena();
	ArenaTile* pNewTile = nullptr;

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::up)))
	{
		pNewTile = pArena->GetNeighbourTile(m_pCurrentTile, GameArena::MovementType::up);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::right)))
	{
		pNewTile = pArena->GetNeighbourTile(m_pCurrentTile, GameArena::MovementType::right);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::down)))
	{
		pNewTile = pArena->GetNeighbourTile(m_pCurrentTile, GameArena::MovementType::down);
	}

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::left)))
	{
		pNewTile = pArena->GetNeighbourTile(m_pCurrentTile, GameArena::MovementType::left);
	}

	if (pNewTile)
	{
		m_pCurrentTile = pNewTile;
	}
}

void QBert::SetTile(ArenaTile* pTile)
{
	m_pCurrentTile = pTile;
}
