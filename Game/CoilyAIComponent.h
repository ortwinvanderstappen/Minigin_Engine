#pragma once
#include "stdafx.h"

#include <Component.h>
#include <memory>

class RandomAIComponent;
class Coily;
class GameArena;
class TileMovementComponent;

class CoilyAIComponent : public minigen::Component
{
public:
	CoilyAIComponent(GameArena* pArena, float aiWaitTime);
	void Initialize() override;
	void Update() override;

private:
	void HandleSnakeMovement();
	float GetAngleToClosestPlayer() const;

	GameArena* m_pArena;
	float m_AiWaitTime;
	float m_AiWaitTimer;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	std::shared_ptr<Coily> m_CoilyScript;
	std::shared_ptr<RandomAIComponent> m_spRandomAIComponent;
};

