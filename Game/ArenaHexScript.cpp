#include "ArenaHexScript.h"
#include "Renderer.h"

#include "GameArenaScript.h"

ArenaHexScript::ArenaHexScript(GameArenaScript* pArena, int row, int column, float size, const Point2i& position) :
	m_pArena(pArena),
	m_Row(row),
	m_Column(column),
	m_Size(size),
	m_Position(position),
	m_IsActive(false)
{}

void ArenaHexScript::Update()
{}

void ArenaHexScript::Render() const
{
	DrawHex(m_Position, m_Size);
}

void ArenaHexScript::DrawHex(Point2i center, float size) const
{
	// Calculate the top polygon points
	std::vector<Point2i> topPoints{};
	topPoints.reserve(4);
	topPoints.push_back(GetHexPoint(center, size, 5));
	topPoints.push_back(GetHexPoint(center, size, 0));
	topPoints.push_back(center);
	topPoints.push_back(GetHexPoint(center, size, 4));
	//DrawFilledPolygon(topPoints, m_InactiveHexColor, pRenderer);
	minigen::Renderer::GetInstance().RenderPolygon(topPoints, Color3f{ 1, 0, 0 });

	// Calculate the right polygon points
	std::vector<Point2i> rightPoints{};
	rightPoints.reserve(4);
	rightPoints.push_back(GetHexPoint(center, size, 0));
	rightPoints.push_back(GetHexPoint(center, size, 1));
	rightPoints.push_back(GetHexPoint(center, size, 2));
	rightPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(rightPoints, Color3f{ 0, 0, 1 });
	// Calculate the left polygon points
	std::vector<Point2i> leftPoints{};
	leftPoints.reserve(4);
	leftPoints.push_back(GetHexPoint(center, size, 2));
	leftPoints.push_back(GetHexPoint(center, size, 3));
	leftPoints.push_back(GetHexPoint(center, size, 4));
	leftPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(leftPoints, Color3f{ 0, 1, 0 });
}

Point2i ArenaHexScript::GetHexPoint(Point2i center, float size, int i) const
{
	const float angle_deg = 60.f * static_cast<float>(i) - 30.f;
	const float angle_rad = static_cast<float>(M_PI) * angle_deg / 180.f;

	const int posX{ static_cast<int>(static_cast<float>(center.x) + size * cos(angle_rad)) };
	const int posY{ static_cast<int>(static_cast<float>(center.y) + size * sin(angle_rad)) };

	return { posX, posY };
}