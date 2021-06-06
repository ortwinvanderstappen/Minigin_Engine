#pragma once
#include <Component.h>
#include <Subject.h>
#include <string>

namespace minigen {
	class SoundComponent;
}

class QBert;
class TileMovementComponent;
class GameArena;
class ArenaTile;

class Coily : public minigen::Component, public minigen::Subject
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

	CoilyState GetState() const;

private:
	void InitializeSprite();
	void InitializeSounds();
	
	void CheckTransformation();
	void TransformIntoSnake();
	void HandleTransformation();

	void HandleTileChange();
	
	GameArena* m_pArena;
	std::shared_ptr<TileMovementComponent> m_spMovementComponent;
	std::vector<std::shared_ptr<QBert>> m_spPlayers;

	std::string m_CoilyBallImagePath;
	std::string m_CoilySnakeImagePath;

	CoilyState m_CoilyState;
	float m_TransformTime;
	float m_TransformTimer;

	std::shared_ptr<minigen::SoundComponent> m_spFallSound;
};

