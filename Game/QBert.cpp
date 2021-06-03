#include "QBert.h"
#include <iostream>
#include "ImageRenderComponent.h"
#include "InputComponent.h"
#include "ArenaTile.h"
#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameArena.h"
#include "GameObject.h"

QBert::QBert(GameArena* pArena, ArenaTile* pStartTile, int playerIndex) :
	m_pArena(pArena),
	m_spMovementComponent(std::make_shared<TileMovementComponent>(pArena, pStartTile, .01f)),
	m_QbertImagePath("images/QBert.png"),
	m_PlayerIndex(playerIndex)
{}

void QBert::Update()
{
	Script::Update();

	ProcessInput();
}

void QBert::Initialize()
{
	m_pParentObject->SetTag("QBert");

	InitializeSprite();
	InitializeControls();

	// Create a collision subject
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 7.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);

	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	// Movement
	AddComponent(m_spMovementComponent);
}

void QBert::InitializeSprite()
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float scale = m_pArena->GetTileSize() / 15.f;
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

void QBert::ProcessInput() const
{
	bool moved = false;

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::up)))
		moved = m_spMovementComponent->Move(TileMovementComponent::MovementType::up);

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::right)))
		moved = m_spMovementComponent->Move(TileMovementComponent::MovementType::right);

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::down)))
		moved = m_spMovementComponent->Move(TileMovementComponent::MovementType::down);

	if (minigen::InputManager::GetInstance().IsInputTriggered(static_cast<int>(InputId::left)))
		moved = m_spMovementComponent->Move(TileMovementComponent::MovementType::left);

	if (moved)
	{
		ArenaTile* pTile = m_spMovementComponent->GetTile();

		if (pTile->IsNullTile() && !pTile->HasDisc())
		{
			Die();
		}

		m_spMovementComponent->GetTile()->Activate();
	}

}

void QBert::Die() const
{
	m_pArena->HandleQbertDeath();
}

void QBert::OnCollisionEnter(minigen::GameObject* const pOtherGameObject)
{
	std::cout << "QBert collided with tagged object: " << pOtherGameObject->GetTag() << "\n";

	if (pOtherGameObject->GetTag() == "Disc")
	{
		m_spMovementComponent->SetTile(m_pArena->GetTopTile());
		m_spMovementComponent->GetTile()->Activate();
	}
	else if (pOtherGameObject->GetTag() == "Coily")
	{
		Die();
	}
}
