#pragma once
#include "stdafx.h"

#include <Component.h>
#include <string>

class ArenaTile;
class GameArena;
struct Point2f;

class FlyingDisc : public minigen::Component
{
public:
	FlyingDisc(GameArena* pArena, ArenaTile* pTile);

	void Update() override;
	void Initialize() override;
	void SetPosition(const Point2f& pos) const;
	void OnCollisionEnter(minigen::GameObject* const pOtherGameObject) override;
private:
	void InitializeSprite();

	GameArena* m_pArena;
	ArenaTile* m_pTile;
	
	std::string m_FlyingDiscImagePath;
	bool m_IsUsed;
};

