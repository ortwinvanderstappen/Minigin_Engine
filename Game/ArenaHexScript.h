#pragma once
#include "Script.h"
#include "structs.h"

class GameArenaScript;
class ArenaHexScript: minigen::Script
{
public:
	ArenaHexScript(GameArenaScript* pArena, int row, int column, float size, const Point2f& position);

	void Update() override;
	void Render() const override;

	const Point2f GetCenter() const;
	const Point2f& GetPosition() const;
private:
	void DrawHex(Point2f center, float size) const;
	const Point2f GetHexPoint(Point2f center, float size, int i) const;
	
	GameArenaScript* m_pArena;
	bool m_IsActive;
	float m_Size;
	int m_Row, m_Column;
	Point2f m_Position;
};

