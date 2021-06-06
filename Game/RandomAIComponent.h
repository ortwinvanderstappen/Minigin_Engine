#pragma once
#include "stdafx.h"

#include <Component.h>
#include <memory>

#include "TileMovementComponent.h"

class TileMovementComponent;
class GameArena;

class RandomAIComponent: public minigen::Component
{
public:
	RandomAIComponent(GameArena* pArena, float aiWaitTime, bool allowNullTile = false, bool onlyAllowBottomNullTile = true);

	void Initialize() override;
	void Update() override;

	void Disable();

private:
	void HandleMovement();
	bool IsRandomMovementTileNull(TileMovementComponent::MovementType movement) const;
	
	GameArena* m_pArena;
	float m_AiWaitTime;
	bool m_AllowNullTile;
	bool m_OnlyAllowBottomNullTile;
	bool m_IsEnabled;
	float m_AiWaitTimer;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
};

