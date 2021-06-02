#pragma once
#include "RenderComponent.h"
#include "structs.h"

class GameArenaScript;
class ArenaHexScript: minigen::RenderComponent
{
public:
	ArenaHexScript(GameArenaScript* pArena, int row, int column, float size, const Point2i& position);

	void Update() override;
	void Render() const override;
private:
	void DrawHex(Point2i center, float size) const;
	Point2i GetHexPoint(Point2i center, float size, int i) const;
	
	GameArenaScript* m_pArena;
	bool m_IsActive;
	float m_Size;
	int m_Row, m_Column;
	Point2i m_Position;
};

