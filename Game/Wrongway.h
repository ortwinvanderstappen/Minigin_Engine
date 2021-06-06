#pragma once
#include <Component.h>
#include <string>
class TileMovementComponent;
class GameArena;
class ArenaTile;

class Wrongway : public minigen::Component
{
public:
	Wrongway(GameArena* pArena, ArenaTile* pTile);
	
	void Initialize() override;
	void Update() override;
	
	void InitializeSprite();

private:
	void HandleTileChange() const;
	
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	float m_MovementDelay;
	std::string m_WrongwayImagePath;
};

