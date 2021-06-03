#pragma once
#include <Component.h>
class GameArena;
class ArenaTile;

class TileMovementComponent : public minigen::Component
{
public:
	enum class MovementType
	{
		up,
		down,
		left,
		right
	};
	
	TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, float movementCooldown = .5f);

	void Initialize() override;
	void Update() override;
	bool Move(MovementType movement);

	void SetTile(ArenaTile* pTile);
	ArenaTile* GetTile() const;
	
	void SetParentPosition() const;

private:
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	float m_MovementCooldown;
	float m_MovementTimer;
};

