#include "stdafx.h"
#include "RandomAIComponent.h"

#include <GameObject.h>
#include <GameTime.h>
#include <iostream>

#include "GameArena.h"
#include "TileMovementComponent.h"

RandomAIComponent::RandomAIComponent(GameArena* pArena, float aiWaitTime, bool allowNullTile, bool onlyAllowBottomNullTile) :
	m_pArena(pArena),
	m_AiWaitTime(aiWaitTime),
	m_AllowNullTile(allowNullTile),
	m_OnlyAllowBottomNullTile(onlyAllowBottomNullTile),
	m_IsEnabled(true),
	m_AiWaitTimer(0.f)
{}

void RandomAIComponent::Initialize()
{
	m_spTileMovementComponent = m_pParentObject->GetComponent<TileMovementComponent>();
	if (m_spTileMovementComponent == nullptr)
	{
		std::cerr << "RandomAIComponent: Required component in Coily: TileMovementComponent not found! Object tag :" << GetParent()->GetTag() << "\n";
	}
}

void RandomAIComponent::Update()
{
	if (!m_IsEnabled) return;

	HandleMovement();
}

void RandomAIComponent::Disable()
{
	m_IsEnabled = false;
}

void RandomAIComponent::HandleMovement()
{
	if (m_spTileMovementComponent->GetMoveState() == TileMovementComponent::MoveState::Idle)
	{
		const float deltaTime = Time::GetInstance().GetDeltaTime();
		m_AiWaitTimer += deltaTime;

		if (m_AiWaitTimer >= m_AiWaitTime)
		{
			m_AiWaitTimer = 0.f;

			// Find all the possible movement options
			std::vector<TileMovementComponent::MovementType> possibleMovements{};
			for (const std::pair<TileMovementComponent::MovementType, bool> movementOption : m_spTileMovementComponent->GetAllowedMovements())
			{
				const TileMovementComponent::MovementType movement = movementOption.first;

				// Don't do movement if set to not allowed
				if (movementOption.second == false) continue;

				// Do extra checks if desired tile is null
				if (IsRandomMovementTileNull(movement))
				{
					if (m_AllowNullTile)
					{
						// Only allow null tiles if they're a bottom tile (jumping off the map)
						if (m_OnlyAllowBottomNullTile)
						{
							const ArenaTile* pNeighbourTile = m_pArena->GetNeighbourTile(m_spTileMovementComponent->GetTile(), movement);
							if (pNeighbourTile)
							{
								if (m_pArena->IsBottomTileIndex(pNeighbourTile->GetIndex()))
								{
									possibleMovements.push_back(movement);
								}
							}
						}
						else
						{
							possibleMovements.push_back(movement);
						}
					}
					// No null tiles allowed
					else
					{
						// Make sure tile is not a null tile
						if (!IsRandomMovementTileNull(movement))
						{
							possibleMovements.push_back(movement);
						}
					}
				}
				// Not a null tile, proceed normally
				else
				{
					possibleMovements.push_back(movement);
				}
			}

			// Don't move if no options were found
			if (possibleMovements.empty()) return;

			// Move to a random possible movement option
			const TileMovementComponent::MovementType randomMovement = possibleMovements[rand() % possibleMovements.size()];
			m_spTileMovementComponent->Move(randomMovement);
		}
	}

}

bool RandomAIComponent::IsRandomMovementTileNull(TileMovementComponent::MovementType movement) const
{
	ArenaTile* pNeighbourTile = m_pArena->GetNeighbourTile(m_spTileMovementComponent->GetTile(), movement);
	if (pNeighbourTile)
		return pNeighbourTile->IsNullTile();

	return true;
}

