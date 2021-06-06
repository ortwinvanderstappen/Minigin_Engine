#include "stdafx.h"
#include "Coily.h"

#include <CollisionObserver.h>
#include <CollisionSubject.h>
#include <GameObject.h>
#include <GameTime.h>
#include <ImageRenderComponent.h>
#include <SoundComponent.h>

#include "ArenaTile.h"
#include "GameArena.h"
#include "GameContext.h"
#include "QBert.h"

Coily::Coily(GameArena* pArena, ArenaTile* pStartTile, const std::vector<std::shared_ptr<QBert>>& spPlayers) :
	m_pArena(pArena),
	m_pStartTile(pStartTile),
	m_spMovementComponent(nullptr),
	m_spPlayers(spPlayers),
	m_CoilyBallImagePath("images/CoilyBall.png"),
	m_CoilySnakeImagePath("images/CoilySnake.png"),
	m_CoilyState(CoilyState::Ball),
	m_TransformTime(2.f),
	m_TransformTimer(0.f)
{}

void Coily::Initialize()
{
	m_pParentObject->SetTag("Coily");
	InitializeSpriteAndCollision();
	InitializeSounds();

	m_spMovementComponent = std::make_shared<TileMovementComponent>(m_pArena, m_pStartTile, 
		GameContext::GetInstance().GetEntityProperty(EntityType::coily)->movespeed);
	auto movedCallback = [this]() { HandleTileChange(); };
	m_spMovementComponent->SubscribeToMoveCompleted(movedCallback);

	// Movement
	m_pParentObject->AddComponent(m_spMovementComponent);
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upRight, false);
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upLeft, false);
}

void Coily::InitializeSpriteAndCollision()
{
	const std::string& path = m_CoilyState == CoilyState::Ball ? m_CoilyBallImagePath : m_CoilySnakeImagePath;
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();
	const float scale = m_pArena->GetTileSize() / 15.f;
	imageRenderComponent->AddImage(path, { -8 * scale,-10 * scale }, scale);
	m_pParentObject->AddComponent(imageRenderComponent);

	// Create a collision subject
	const Point2f collisionSize = { 8.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);
	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);
}

void Coily::InitializeSounds()
{
	m_spFallSound = std::make_shared<minigen::SoundComponent>("Data/audio/SnakeFall.wav");
	GetParent()->AddComponent(m_spFallSound);
}

void Coily::Update()
{
	if (m_CoilyState == CoilyState::Transforming)
	{
		HandleTransformation();
	}
}

void Coily::OnCollisionEnter(minigen::GameObject* const)
{

}

void Coily::TransformIntoSnake()
{
	Notify(GetParent(), minigen::Observer::Event::event_coily_transform);

	// Enable all movements
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upRight, true);
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upLeft, true);
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::downLeft, true);
	m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::downRight, true);

	m_CoilyState = CoilyState::Snake;
	std::shared_ptr<minigen::ImageRenderComponent> spImageComponent = m_pParentObject->GetComponent<minigen::ImageRenderComponent>();
	if (spImageComponent)
	{
		spImageComponent->RemoveImage(m_CoilyBallImagePath);
		InitializeSpriteAndCollision();
	}
}

Coily::CoilyState Coily::GetState() const
{
	return m_CoilyState;
}

void Coily::CheckTransformation()
{
	// Coily should start transforming if he reaches the bottom tile
	if (m_pArena->IsBottomTileIndex(m_spMovementComponent->GetTile()->GetIndex()))
	{
		// Disable all movements
		m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upRight, false);
		m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upLeft, false);
		m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::downLeft, false);
		m_spMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::downRight, false);

		m_CoilyState = CoilyState::Transforming;
	}
}

void Coily::HandleTransformation()
{
	const float deltaTime = Time::GetInstance().DeltaTime();

	m_TransformTimer += deltaTime;
	if (m_TransformTimer >= m_TransformTime)
	{
		TransformIntoSnake();
	}
}

void Coily::HandleTileChange()
{
	if (m_spMovementComponent->GetTile()->IsNullTile())
	{
		m_spFallSound->PlaySoundEffect();
		Notify(GetParent(), minigen::Observer::Event::event_coily_fall);
		m_pParentObject->MarkForDelete();
	}
	else if (m_CoilyState == CoilyState::Ball)
	{
		CheckTransformation();
	}
}
