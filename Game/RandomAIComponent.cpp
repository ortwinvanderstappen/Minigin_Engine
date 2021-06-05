#include "RandomAIComponent.h"

#include <iostream>


#include "GameArena.h"
#include "GameObject.h"
#include "GameTime.h"
#include "TileMovementComponent.h"

RandomAIComponent::RandomAIComponent(GameArena* pArena, float movementDelay, bool allowNullTile, bool onlyAllowBottomNullTile) :
	m_pArena(pArena),
	m_MovementDelay(movementDelay),
	m_AllowNullTile(allowNullTile),
	m_OnlyAllowBottomNullTile(onlyAllowBottomNullTile),
	m_MovementTimer(0.f),
	m_IsEnabled(true),
	m_AllowedMovementsMap()
{}

void RandomAIComponent::Initialize()
{
	m_spTileMovementComponent = m_pParentObject->GetComponent<TileMovementComponent>();
	if (m_spTileMovementComponent == nullptr)
	{
		std::cerr << "RandomAIComponent: Required component in Coily: TileMovementComponent not found! Object tag :" << GetParent()->GetTag() << "\n";
	}

	// Setup allowed movements map (allow all movements by default)
	for (int i = 0; i < 4; ++i)
	{
		m_AllowedMovementsMap.insert(std::make_pair(static_cast<TileMovementComponent::MovementType>(i), true));
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

void RandomAIComponent::SetMovementAllowed(TileMovementComponent::MovementType movement, bool state)
{
	m_AllowedMovementsMap[movement] = state;
}

void RandomAIComponent::HandleMovement()
{
	IncreaseMovementTimer();
	if (m_MovementTimer > m_MovementDelay)
	{
		m_MovementTimer -= m_MovementDelay;

		// Find all the possible movement options
		std::vector<TileMovementComponent::MovementType> possibleMovements{};
		for (const std::pair<TileMovementComponent::MovementType, bool> movementOption : m_AllowedMovementsMap)
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
						if (m_pArena->IsBottomTileIndex(pNeighbourTile->GetIndex()))
						{
							possibleMovements.push_back(movement);
						}
					} else
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
		if(possibleMovements.empty()) return;
		
		// Move to a random possible movement option
		m_spTileMovementComponent->Move(possibleMovements[rand() % possibleMovements.size()]);
	}
}

void RandomAIComponent::IncreaseMovementTimer()
{
	const float deltaTime = Time::GetInstance().DeltaTime();
	m_MovementTimer += deltaTime;
}

bool RandomAIComponent::IsRandomMovementTileNull(TileMovementComponent::MovementType movement) const
{
	ArenaTile* pNeighbourTile = m_pArena->GetNeighbourTile(m_spTileMovementComponent->GetTile(), movement);
	if (pNeighbourTile)
		return pNeighbourTile->IsNullTile();

	return true;
}

