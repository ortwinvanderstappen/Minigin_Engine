#pragma once
#include "Script.h"
#include "structs.h"

class FlyingDisc;
class GameArena;
class ArenaTile : minigen::Script
{
public:
	ArenaTile(GameArena* pArena,int index, float size, const Point2f& position, bool isNullTile);

	void Update() override;
	void Render() const override;

	Point2f GetCenter() const;
	const Point2f& GetPosition() const;

	int GetIndex() const;
	GameArena* GetArena() const;

	void AttachFlyingDisc(std::shared_ptr<FlyingDisc> spDisc);
	
	void Activate();
private:
	void DrawHex(Point2f center, float size) const;
	const Point2f GetHexPoint(Point2f center, float size, int i) const;

	GameArena* m_pArena;
	int m_Index;
	float m_Size;
	Point2f m_Position;
	bool m_IsNullTile;
	
	bool m_IsActive;
	std::shared_ptr<FlyingDisc> m_spDisc;
};

