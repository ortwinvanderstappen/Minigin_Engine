#pragma once
#include "stdafx.h"

#include <Component.h>
#include <Subject.h>
#include <string>

namespace minigen {
	class SoundComponent;
}

class TileMovementComponent;
class GameArena;
class ArenaTile;
class QBert : public minigen::Component, public minigen::Subject
{
public:
	QBert(GameArena* pArena, ArenaTile* pStartTile);
	void Update() override{};
	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
protected:
	void Initialize() override;
private:
	void InitializeSprite() const;
	void InitializeSounds();
	void Die();

	void HandleTileChange();
	void HandleMove() const;
	
	GameArena* m_pArena;
	ArenaTile* m_pSpawnTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	std::string m_QbertImagePath;

	std::shared_ptr<minigen::SoundComponent> m_spDeathSoundComponent;
	std::shared_ptr<minigen::SoundComponent> m_spFallSoundComponent;
	std::shared_ptr<minigen::SoundComponent> m_spJumpSoundComponent;
	std::shared_ptr<minigen::SoundComponent> m_spLiftSoundComponent;
};