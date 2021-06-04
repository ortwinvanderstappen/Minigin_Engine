#pragma once
#include <Component.h>
class Coily;
class GameArena;
class TileMovementComponent;

class CoilyAIComponent : public minigen::Component
{
public:
	CoilyAIComponent(GameArena* pArena);
	void Initialize() override;
	void Update() override;

private:
	
	void IncreaseMovementTimer();
	void HandleBallMovement();
	void HandleSnakeMovement();
	bool IsRandomMovementTileNull(int movementDirection) const;
	float GetAngleToClosestPlayer() const;

	GameArena* m_pArena;
	float m_MovementTimer;
	float m_MovementDelay;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	std::shared_ptr<Coily> m_CoilyScript;
};

