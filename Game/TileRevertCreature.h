#pragma once
#include "stdafx.h"

#include <Component.h>
#include <Subject.h>

class ArenaTile;
class GameArena;
class TileMovementComponent;

class TileRevertCreature : public minigen::Component, public minigen::Subject
{
public:
	enum class CreatureType
	{
		Slick,
		Sam
	};
	TileRevertCreature(GameArena* pArena, ArenaTile* pStartTile, CreatureType type);
	
	void Initialize() override;
	void Update() override;
	void OnCollisionEnter(minigen::GameObject* const) override;

private:
	void InitializeSprite();
	
	GameArena* m_pArena;
	ArenaTile* m_pStartTile;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
	CreatureType m_CreatureType;
	std::string m_SlickTexturePath;
	std::string m_SamTexturePath;
};

