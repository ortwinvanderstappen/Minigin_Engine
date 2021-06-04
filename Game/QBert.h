#pragma once
#include <string>
#include "Script.h"

class TileMovementComponent;
class GameArena;
class ArenaTile;
class QBert : public minigen::Script
{
public:
	QBert(GameArena* pArena, ArenaTile* pStartTile);
	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
protected:
	void Initialize() override;
private:
	void InitializeSprite() const;
	void Die() const;

	void HandleTileChange() const;
	
	GameArena* m_pArena;
	ArenaTile* m_pSpawnTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	
	std::string m_QbertImagePath;
};