#pragma once
#include <Script.h>
#include <string>

class QBert;
class TileMovementComponent;
class GameArena;
class ArenaTile;

class Coily : public minigen::Script
{
public:
	Coily(GameArena* pArena, ArenaTile* pStartTile, const std::vector<std::shared_ptr<QBert>>& spPlayers);
	~Coily();

	void Initialize() override;
	void Update() override;
	void OnCollisionEnter(minigen::GameObject* const) override;

	void InitializeSprite();
	void TransformIntoSnake();

	void IncreaseMovementTimer();
private:
	void HandleBallMovement();
	void HandleSnakeMovement();
	bool IsRandomMovementTileNull(int movementDirection) const;
	float GetAngleToClosestPlayer() const;
	
	enum class CoilyState
	{
		Ball,
		Transforming,
		Snake
	};

	GameArena* m_pArena;
	std::shared_ptr<TileMovementComponent> m_spMovementComponent;
	std::vector<std::shared_ptr<QBert>> m_spPlayers;

	std::string m_CoilyBallImagePath;
	std::string m_CoilySnakeImagePath;

	CoilyState m_CoilyState;
	float m_TransformTime;
	float m_TransformTimer;

	float m_MovementDelay;
	float m_MovementTimer;
};

