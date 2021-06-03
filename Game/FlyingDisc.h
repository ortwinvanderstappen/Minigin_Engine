#pragma once
#include <Script.h>
#include <string>

class ArenaTile;
class GameArena;
struct Point2f;

class FlyingDisc : public minigen::Script
{
public:
	FlyingDisc(GameArena* pArena, ArenaTile* pTile);

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

