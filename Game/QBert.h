#pragma once
#include <string>
#include "Component.h"
#include "Subject.h"

class TileMovementComponent;
class GameArena;
class ArenaTile;
class QBert : public minigen::Component, public minigen::Subject
{
public:
	QBert(GameArena* pArena, ArenaTile* pStartTile);
	void Update() override;
	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
protected:
	void Initialize() override;
private:
	void InitializeSprite() const;
	void Die();

	void HandleTileChange();
	
	GameArena* m_pArena;
	ArenaTile* m_pSpawnTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	
	std::string m_QbertImagePath;
	bool m_Died;
};