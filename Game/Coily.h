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
	enum class CoilyState
	{
		Ball,
		Transforming,
		Snake
	};
	
	Coily(GameArena* pArena, ArenaTile* pStartTile, const std::vector<std::shared_ptr<QBert>>& spPlayers);

	void Initialize() override;
	void Update() override;
	void OnCollisionEnter(minigen::GameObject* const) override;

	void InitializeSprite();
	void TransformIntoSnake();

	CoilyState GetState() const;

private:
	void CheckTransformation();
	void HandleTransformation();
	
	GameArena* m_pArena;
	std::shared_ptr<TileMovementComponent> m_spMovementComponent;
	std::vector<std::shared_ptr<QBert>> m_spPlayers;

	std::string m_CoilyBallImagePath;
	std::string m_CoilySnakeImagePath;

	CoilyState m_CoilyState;
	float m_TransformTime;
	float m_TransformTimer;
};

