#pragma once
#include "Component.h"

class TileMovementComponent;
class GameArena;
class ArenaTile;

class Ugg: public minigen::Component
{
public:
	Ugg(GameArena* pArena, ArenaTile* pTile);

	void Initialize() override;
	void Update() override;

private:
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	float m_MovementDelay;
};

