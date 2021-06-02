#pragma once
#include "Script.h"
#include "structs.h"

class GameArenaScript;
class ArenaHexScript : minigen::Script
{
public:
	ArenaHexScript(GameArenaScript* pArena,int index, int row, int column, float size, const Point2f& position, bool isNullTile);

	void Update() override;
	void Render() const override;

	const Point2f GetCenter() const;
	const Point2f& GetPosition() const;

	int GetIndex() const;
	int GetRow() const;
	int GetColumn() const;
	GameArenaScript* GetArena() const;
	
	void Activate();
private:
	void DrawHex(Point2f center, float size) const;
	const Point2f GetHexPoint(Point2f center, float size, int i) const;

	GameArenaScript* m_pArena;
	int m_Index;
	int m_Row;
	int m_Column;
	bool m_IsActive;
	float m_Size;
	Point2f m_Position;
	bool m_IsNullTile;
};

