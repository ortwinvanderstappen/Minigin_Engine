#pragma once
#include <string>
#include "Component.h"

class TileMovementComponent;
class GameArena;
class ArenaTile;
class QBert : public minigen::Component
{
public:
	QBert(GameArena* pArena, ArenaTile* pStartTile);
	void Update() override;
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