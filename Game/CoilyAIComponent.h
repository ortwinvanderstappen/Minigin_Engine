#pragma once
#include <Component.h>
class RandomAIComponent;
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
	float GetAngleToClosestPlayer() const;

	GameArena* m_pArena;
	float m_MovementTimer;
	float m_MovementDelay;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	std::shared_ptr<Coily> m_CoilyScript;
	std::shared_ptr<RandomAIComponent> m_spRandomAIComponent;
};

