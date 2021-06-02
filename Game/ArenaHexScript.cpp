#include "ArenaHexScript.h"
#include "Renderer.h"

#include "GameArenaScript.h"

ArenaHexScript::ArenaHexScript(GameArenaScript* pArena, int index, int row, int column, float size, const Point2f& position, bool isNullTile) :
	m_pArena(pArena),
	m_Index(index),
	m_Row(row),
	m_Column(column),
	m_Size(size),
	m_Position(position),
	m_IsActive(false),
	m_IsNullTile(isNullTile)
{}

void ArenaHexScript::Update()
{}

void ArenaHexScript::Render() const
{
	//if (!m_IsNullTile)
	DrawHex(m_Position, m_Size);
}

const Point2f ArenaHexScript::GetCenter() const
{
	return m_Position + Point2f{ 0.f,-m_Size * .5f };
}

const Point2f& ArenaHexScript::GetPosition() const
{
	return m_Position;
}

int ArenaHexScript::GetIndex() const
{
	return m_Index;
}

int ArenaHexScript::GetRow() const
{
	return m_Row;
}

int ArenaHexScript::GetColumn() const
{
	return m_Column;
}

GameArenaScript* ArenaHexScript::GetArena() const
{
	return m_pArena;
}

void ArenaHexScript::Activate()
{
	m_IsActive = true;
}

void ArenaHexScript::DrawHex(Point2f center, float size) const
{
	const Color3i& topColorI = m_IsActive ? m_pArena->GetPrimaryColor() : m_pArena->GetSecondaryColor();
	Color3f topColor = Color3f{ static_cast<float>(topColorI.r) / 255.f,static_cast<float>(topColorI.g) / 255.f,static_cast<float>(topColorI.b) / 255.f };
	const Color3i bottomColorI = m_pArena->GetSecondaryColor();
	const Color3f bottomColor = Color3f{ static_cast<float>(bottomColorI.r) / 255.f,static_cast<float>(bottomColorI.g) / 255.f,static_cast<float>(bottomColorI.b) / 255.f };

	const float colorOffset = .1f;
	Color3f leftColor = Color3f{ bottomColor.r - colorOffset, bottomColor.g - colorOffset, bottomColor.b - colorOffset };
	Color3f rightColor = Color3f{ bottomColor.r + colorOffset, bottomColor.g + colorOffset, bottomColor.b + colorOffset };

	if (m_IsNullTile)
	{
		leftColor.r -= 20.f;
		rightColor.r -= 20.f;
		topColor.r -= 20.f;
	}

	// Calculate the top polygon points
	std::vector<Point2f> topPoints{};
	topPoints.reserve(4);
	topPoints.push_back(GetHexPoint(center, size, 5));
	topPoints.push_back(GetHexPoint(center, size, 0));
	topPoints.push_back(center);
	topPoints.push_back(GetHexPoint(center, size, 4));
	minigen::Renderer::GetInstance().RenderPolygon(topPoints, topColor);

	// Calculate the right polygon points
	std::vector<Point2f> rightPoints{};
	rightPoints.reserve(4);
	rightPoints.push_back(GetHexPoint(center, size, 0));
	rightPoints.push_back(GetHexPoint(center, size, 1));
	rightPoints.push_back(GetHexPoint(center, size, 2));
	rightPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(rightPoints, rightColor);
	// Calculate the left polygon points
	std::vector<Point2f> leftPoints{};
	leftPoints.reserve(4);
	leftPoints.push_back(GetHexPoint(center, size, 2));
	leftPoints.push_back(GetHexPoint(center, size, 3));
	leftPoints.push_back(GetHexPoint(center, size, 4));
	leftPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(leftPoints, leftColor);
}

const Point2f ArenaHexScript::GetHexPoint(Point2f center, float size, int i) const
{
	const float angle_deg = 60.f * static_cast<float>(i) - 30.f;
	const float angle_rad = static_cast<float>(M_PI) * angle_deg / 180.f;

	const float posX{ static_cast<float>(center.x) + size * cos(angle_rad) };
	const float posY{ static_cast<float>(center.y) + size * sin(angle_rad) };

	return { posX, posY };
}