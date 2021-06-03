#pragma once
#include <string>
#include "Script.h"

class TileMovementComponent;
class GameArena;
class ArenaTile;
class QBert : public minigen::Script
{
public:
	QBert(GameArena* pArena, ArenaTile* pStartTile, int playerIndex);
	void Update() override;
	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
protected:
	void Initialize() override;
private:
	enum class InputId
	{
		up,
		right,
		down,
		left
	};
	
	void InitializeSprite();
	void InitializeControls();
	void ProcessInput() const;
	void Die() const;

	GameArena* m_pArena;
	std::shared_ptr<TileMovementComponent> m_spMovementComponent;
	
	std::string m_QbertImagePath;
	int m_PlayerIndex;
};