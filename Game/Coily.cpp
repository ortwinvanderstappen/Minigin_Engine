#include "Coily.h"

#include <iostream>

#include "ImageRenderComponent.h"
#include "GameArena.h"
#include "ArenaTile.h"
#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameObject.h"
#include "GameTime.h"
#include "QBert.h"
#include <SDL_stdinc.h>

Coily::Coily(GameArena* pArena, ArenaTile* pStartTile, const std::vector<std::shared_ptr<QBert>>& spPlayers) :
	m_pArena(pArena),
	m_spMovementComponent(std::make_shared<TileMovementComponent>(pArena, pStartTile, 0.f)),
	m_spPlayers(spPlayers),
	m_CoilyBallImagePath("images/CoilyBall.png"),
	m_CoilySnakeImagePath("images/CoilySnake.png"),
	m_CoilyState(CoilyState::Ball),
	m_TransformTime(2.f),
	m_TransformTimer(0.f),
	m_MovementTimer(0.f),
	m_MovementDelay(1.0f)
{}

Coily::~Coily()
{
	std::cout << "Destructor Coily!\n";
}

void Coily::Initialize()
{
	m_pParentObject->SetTag("Coily");
	InitializeSprite();

	// Create a collision subject
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 8.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);

	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	// Movement
	AddComponent(m_spMovementComponent);
}

void Coily::InitializeSprite()
{
	const std::string& path = m_CoilyState == CoilyState::Ball ? m_CoilyBallImagePath : m_CoilySnakeImagePath;
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();
	const float scale = m_pArena->GetTileSize() / 15.f;
	imageRenderComponent->AddImage(path, { -8 * scale,-10 * scale }, scale);
	AddComponent(imageRenderComponent);
}

void Coily::Update()
{
	const float deltaTime = Time::GetInstance().DeltaTime();

	switch (m_CoilyState)
	{
	case CoilyState::Ball:
		HandleBallMovement();
		break;
	case CoilyState::Transforming:
		m_TransformTimer += deltaTime;
		if (m_TransformTimer > m_TransformTime)
			TransformIntoSnake();
		break;
	case CoilyState::Snake:
		HandleSnakeMovement();
		break;
	default:;
	}
}

void Coily::OnCollisionEnter(minigen::GameObject* const)
{

}

void Coily::TransformIntoSnake()
{
	m_CoilyState = CoilyState::Snake;
	std::shared_ptr<minigen::ImageRenderComponent> spImageComponent = GetComponent<minigen::ImageRenderComponent>();
	if (spImageComponent)
	{
		spImageComponent->RemoveImage(m_CoilyBallImagePath);
		InitializeSprite();
	}
}

void Coily::IncreaseMovementTimer()
{
	const float deltaTime = Time::GetInstance().DeltaTime();
	m_MovementTimer += deltaTime;
}

void Coily::HandleBallMovement()
{
	IncreaseMovementTimer();
	if (m_MovementTimer > m_MovementDelay)
	{
		m_MovementTimer -= m_MovementDelay;
		int movementDirection = rand() % 2;

		// Check if the tile to move to is a null tile
		if (IsRandomMovementTileNull(movementDirection))
		{
			// Try another direction
			movementDirection = (movementDirection + 1) % 2;
			if (IsRandomMovementTileNull(movementDirection))
			{
				// We have reached the bottom of the pyramid, start transforming
				TransformIntoSnake();
				return;
			}
		}

		// A correct tile was found, move
		m_spMovementComponent->Move(static_cast<TileMovementComponent::MovementType>(movementDirection));
	}
}

void Coily::HandleSnakeMovement()
{
	IncreaseMovementTimer();
	if (m_MovementTimer > m_MovementDelay)
	{
		m_MovementTimer -= m_MovementDelay;

		// Move towards the player
		const float angleToClosestPlayer = GetAngleToClosestPlayer();
		std::cout << "Coily: angle to cloest player: " << angleToClosestPlayer << "\n";

		// Move towards the correct tile
		if(angleToClosestPlayer >= 0 && angleToClosestPlayer <= static_cast<float>(M_PI / 2))
		{
			m_spMovementComponent->Move(TileMovementComponent::MovementType::left);
		} else if(angleToClosestPlayer >= static_cast<float>(M_PI/2) && angleToClosestPlayer <= static_cast<float>(M_PI))
		{
			m_spMovementComponent->Move(TileMovementComponent::MovementType::up);
		} else if(angleToClosestPlayer <= 0.f && angleToClosestPlayer >= -static_cast<float>(M_PI/2))
		{
			m_spMovementComponent->Move(TileMovementComponent::MovementType::down);
		} else
		{
			m_spMovementComponent->Move(TileMovementComponent::MovementType::right);
		}
	}
}

bool Coily::IsRandomMovementTileNull(int movementDirection) const
{
	return m_pArena->GetNeighbourTile(m_spMovementComponent->GetTile(), static_cast<TileMovementComponent::MovementType>(movementDirection))->IsNullTile();
}

float Coily::GetAngleToClosestPlayer() const
{
	const glm::vec3& coilyPosition = GetParent()->GetPosition();

	std::shared_ptr<QBert> spClosestPlayer = m_spPlayers[0];
	float closestDistance = FLT_MAX;
	for (const std::shared_ptr<QBert>& spPlayer : m_spPlayers)
	{
		if (spClosestPlayer == spPlayer) continue;

		// Calculate distance between gameobjects
		const glm::vec3& playerPosition = spPlayer->GetParent()->GetPosition();
		const float distance{ glm::distance(playerPosition, coilyPosition) };
		if (distance < closestDistance)
		{
			spClosestPlayer = spPlayer;
			closestDistance = distance;
		}
	}

	const glm::vec3& playerPosition = spClosestPlayer->GetParent()->GetPosition();
	return atan2(coilyPosition.y - playerPosition.y, coilyPosition.x - playerPosition.x);
}
