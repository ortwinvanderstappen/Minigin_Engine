#pragma once
#include <unordered_map>

#include "Component.h"
#include "TileMovementComponent.h"

class TileMovementComponent;
class GameArena;

class RandomAIComponent: public minigen::Component
{
public:
	RandomAIComponent(GameArena* pArena, float movementDelay = 1.f, bool allowNullTile = false, bool onlyAllowBottomNullTile = true);

	void Initialize() override;
	void Update() override;

	void Disable();

private:
	void HandleMovement();
	void IncreaseMovementTimer();
	bool IsRandomMovementTileNull(TileMovementComponent::MovementType movement) const;
	
	GameArena* m_pArena;
	float m_MovementDelay;
	bool m_AllowNullTile;
	bool m_OnlyAllowBottomNullTile;
	
	float m_MovementTimer;
	bool m_IsEnabled;
	
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
};

