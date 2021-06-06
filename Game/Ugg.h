#pragma once
#include "stdafx.h"

#include <Component.h>
#include <memory>
#include <string>

class TileMovementComponent;
class GameArena;
class ArenaTile;

class Ugg: public minigen::Component
{
public:
	Ugg(GameArena* pArena, ArenaTile* pTile);

	void Initialize() override;
	void Update() override;
	
	void InitializeSprite();

private:
	void HandleTileChange() const;
	
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	float m_MovementDelay;
	std::string m_UggImagePath;
};

