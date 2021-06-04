#include "CoilyAIComponent.h"

#include "GameObject.h"
#include <iostream>
#include "GameArena.h"
#include "GameTime.h"
#include <SDL_stdinc.h>


#include "Coily.h"
#include "QBert.h"

CoilyAIComponent::CoilyAIComponent(GameArena* pArena) :
	m_pArena(pArena),
	m_MovementTimer(0.f),
	m_MovementDelay(1.0f)
{}

void CoilyAIComponent::Initialize()
{
	m_CoilyScript = m_pParentObject->GetScript<Coily>();
	if (m_CoilyScript == nullptr)
	{
		std::cerr << "CoilyAIComponent: Required component in parent: Coily not found!\n";
		return;
	}
	
	m_spTileMovementComponent = m_pParentObject->GetComponent<TileMovementComponent>();
	if (m_spTileMovementComponent == nullptr)
	{
		std::cerr << "CoilyAIComponent: Required component in Coily: TileMovementComponent not found!\n";
	}
}

void CoilyAIComponent::Update()
{
	switch (m_CoilyScript->GetState())
	{
	case Coily::CoilyState::Ball:
		HandleBallMovement();
		break;
	case Coily::CoilyState::Snake:
		HandleSnakeMovement();
		break;
	}
}

void CoilyAIComponent::IncreaseMovementTimer()
{
	const float deltaTime = Time::GetInstance().DeltaTime();
	m_MovementTimer += deltaTime;
}

void CoilyAIComponent::HandleBallMovement()
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
				// We have reached the bottom of the pyramid, no more movement allowed
				return;
			}
		}

		// A correct tile was found, move
		m_spTileMovementComponent->Move(static_cast<TileMovementComponent::MovementType>(movementDirection));
	}
}

void CoilyAIComponent::HandleSnakeMovement()
{
	IncreaseMovementTimer();
	if (m_MovementTimer > m_MovementDelay)
	{
		m_MovementTimer -= m_MovementDelay;

		// Move towards the player
		const float angleToClosestPlayer = GetAngleToClosestPlayer();
		std::cout << "Coily: angle to cloest player: " << angleToClosestPlayer << "\n";

		// Move towards the correct tile
		if (angleToClosestPlayer >= 0 && angleToClosestPlayer <= static_cast<float>(M_PI / 2))
		{
			m_spTileMovementComponent->Move(TileMovementComponent::MovementType::left);
		}
		else if (angleToClosestPlayer >= static_cast<float>(M_PI / 2) && angleToClosestPlayer <= static_cast<float>(M_PI))
		{
			m_spTileMovementComponent->Move(TileMovementComponent::MovementType::up);
		}
		else if (angleToClosestPlayer <= 0.f && angleToClosestPlayer >= -static_cast<float>(M_PI / 2))
		{
			m_spTileMovementComponent->Move(TileMovementComponent::MovementType::down);
		}
		else
		{
			m_spTileMovementComponent->Move(TileMovementComponent::MovementType::right);
		}
	}
}

bool CoilyAIComponent::IsRandomMovementTileNull(int movementDirection) const
{
	return m_pArena->GetNeighbourTile(m_spTileMovementComponent->GetTile(), static_cast<TileMovementComponent::MovementType>(movementDirection))->IsNullTile();
}

float CoilyAIComponent::GetAngleToClosestPlayer() const
{
	const glm::vec3& coilyPosition = m_pParentObject->GetPosition();

	std::vector<std::shared_ptr<QBert>> spPlayers = m_pArena->GetPlayers();

	std::shared_ptr<QBert> spClosestPlayer = spPlayers[0];
	float closestDistance = FLT_MAX;
	for (const std::shared_ptr<QBert>& spPlayer : spPlayers)
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
