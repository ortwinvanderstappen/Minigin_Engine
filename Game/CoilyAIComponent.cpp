#include "stdafx.h"
#include "CoilyAIComponent.h"

#include <GameObject.h>
#include <iostream>
#include <SDL_stdinc.h>

#include "Coily.h"
#include "GameArena.h"
#include "GameContext.h"
#include "GameTime.h"
#include "QBert.h"
#include "RandomAIComponent.h"

CoilyAIComponent::CoilyAIComponent(GameArena* pArena, float aiWaitTime) :
	m_pArena(pArena),
	m_AiWaitTime(aiWaitTime),
	m_AiWaitTimer(0.f)
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

	const float aiWaitTime = GameContext::GetInstance().GetEntityProperty(EntityType::coily)->aiWaitTime;
	m_spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena, aiWaitTime);
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
	default:;
	}
}

void CoilyAIComponent::HandleSnakeMovement()
{
	if (m_spTileMovementComponent->GetMoveState() == TileMovementComponent::MoveState::Idle)
	{
		const float deltaTime = Time::GetInstance().GetDeltaTime();
		m_AiWaitTimer += deltaTime;
		if (m_AiWaitTimer >= m_AiWaitTime)
		{
			m_AiWaitTimer = 0.f;

			// Move towards the player
			const float angleToClosestPlayer = GetAngleToClosestPlayer();

			// Move towards the correct tile
			if (angleToClosestPlayer >= 0 && angleToClosestPlayer <= static_cast<float>(M_PI / 2))
			{
				m_spTileMovementComponent->Move(TileMovementComponent::MovementType::upLeft);
			}
			else if (angleToClosestPlayer >= static_cast<float>(M_PI / 2) && angleToClosestPlayer <= static_cast<float>(M_PI))
			{
				m_spTileMovementComponent->Move(TileMovementComponent::MovementType::upRight);
			}
			else if (angleToClosestPlayer <= 0.f && angleToClosestPlayer >= -static_cast<float>(M_PI / 2))
			{
				m_spTileMovementComponent->Move(TileMovementComponent::MovementType::downLeft);
			}
			else
			{
				m_spTileMovementComponent->Move(TileMovementComponent::MovementType::downRight);
			}
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
