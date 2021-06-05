#include "CoilyAIComponent.h"

#include "GameObject.h"
#include <iostream>
#include "GameArena.h"
#include "GameTime.h"
#include <SDL_stdinc.h>


#include "Coily.h"
#include "QBert.h"
#include "RandomAIComponent.h"

CoilyAIComponent::CoilyAIComponent(GameArena* pArena) :
	m_pArena(pArena),
	m_MovementTimer(0.f),
	m_MovementDelay(1.0f)
{}

void CoilyAIComponent::Initialize()
{
	m_CoilyScript = m_pParentObject->GetComponent<Coily>();
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

	m_spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena, 1.f);
	m_spRandomAIComponent->SetMovementAllowed(TileMovementComponent::MovementType::up, false);
	m_spRandomAIComponent->SetMovementAllowed(TileMovementComponent::MovementType::left, false);
	GetParent()->AddComponent(m_spRandomAIComponent);
}

void CoilyAIComponent::Update()
{
	switch (m_CoilyScript->GetState())
	{
	case Coily::CoilyState::Ball:
		break;
	case Coily::CoilyState::Transforming: 
		m_spRandomAIComponent->Disable();
		break;
	case Coily::CoilyState::Snake:
		HandleSnakeMovement();
		break;
	default: ;
	}
}

void CoilyAIComponent::IncreaseMovementTimer()
{
	const float deltaTime = Time::GetInstance().DeltaTime();
	m_MovementTimer += deltaTime;
}

void CoilyAIComponent::HandleSnakeMovement()
{
	IncreaseMovementTimer();
	if (m_MovementTimer > m_MovementDelay)
	{
		m_MovementTimer -= m_MovementDelay;

		// Move towards the player
		const float angleToClosestPlayer = GetAngleToClosestPlayer();

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

float CoilyAIComponent::GetAngleToClosestPlayer() const
{
	const Point2f& coilyPosition = m_pParentObject->GetPosition();

	std::vector<std::shared_ptr<QBert>> spPlayers = m_pArena->GetPlayers();

	std::shared_ptr<QBert> spClosestPlayer = spPlayers[0];
	float closestDistance = FLT_MAX;
	for (const std::shared_ptr<QBert>& spPlayer : spPlayers)
	{
		if (spClosestPlayer == spPlayer) continue;

		// Calculate distance between gameobjects
		const Point2f& playerPosition = spPlayer->GetParent()->GetPosition();
		const float distance{ playerPosition.Distance(coilyPosition) };
		if (distance < closestDistance)
		{
			spClosestPlayer = spPlayer;
			closestDistance = distance;
		}
	}

	const Point2f& playerPosition = spClosestPlayer->GetParent()->GetPosition();
	return atan2(coilyPosition.y - playerPosition.y, coilyPosition.x - playerPosition.x);
}
