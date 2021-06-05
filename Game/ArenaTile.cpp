#include "ArenaTile.h"

#include <iostream>

#include "Renderer.h"

#include "GameArena.h"

ArenaTile::ArenaTile(GameArena* pArena, int index, float size, const Point2f& position, bool isNullTile, GameManager::StageSettings* pStageSettings) :
	m_pArena(pArena),
	m_Index(index),
	m_Size(size),
	m_Position(position),
	m_IsNullTile(isNullTile),
	m_pStageSettings(pStageSettings),
	m_ColorState(0),
	m_spDisc(nullptr)
{}

void ArenaTile::Update()
{}

void ArenaTile::Render() const
{
	if (!m_IsNullTile)
		DrawHex(m_Position, m_Size);
}

Point2f ArenaTile::GetCenter() const
{
	if (m_IsNullTile)
	{
		return m_Position + Point2f{ 0.f, m_Size * .5f };
	}

	return m_Position + Point2f{ 0.f,-m_Size * .5f };
}

const Point2f& ArenaTile::GetPosition() const
{
	return m_Position;
}

int ArenaTile::GetIndex() const
{
	return m_Index;
}

GameArena* ArenaTile::GetArena() const
{
	return m_pArena;
}

bool ArenaTile::IsNullTile() const
{
	return m_IsNullTile;
}

bool ArenaTile::HasDisc() const
{
	return m_spDisc != nullptr;
}

bool ArenaTile::IsComplete() const
{
	return m_ColorState == static_cast<int>(m_pStageSettings->activeColors.size());
}

void ArenaTile::AttachFlyingDisc(const std::shared_ptr<FlyingDisc>& spDisc)
{
	if (m_spDisc)
		std::cout << "Tile " << m_Index << " already has a flying disc attached (overwriting...)\n";

	m_spDisc = spDisc;
}

void ArenaTile::Activate()
{
	if(m_IsNullTile) return;
	
	const int previousColor = m_ColorState;
	const int activeColors = static_cast<int>(m_pStageSettings->activeColors.size());
	
	++m_ColorState;
	if (m_pStageSettings->cyclesColor)
	{
		m_ColorState %= (activeColors + 1);
		if (m_ColorState == 0)
		{
		Notify(GetParent(), minigen::Observer::Event::event_tile_uncomplete);
			//m_pArena->IncreaseCompletedTiles(-1);
		}
	}
	else
	{
		if (m_ColorState > activeColors)
		{
			m_ColorState = activeColors;
		}
	}

	// Is this the last color state and did the state change?
	if (m_ColorState == activeColors && previousColor != m_ColorState)
	{
		Notify(GetParent(), minigen::Observer::Event::event_tile_complete);
		//m_pArena->IncreaseCompletedTiles(1);
	}
}

void ArenaTile::DrawHex(Point2f center, float size) const
{
	Color3i topColorI;
	if (m_ColorState == 0)
	{
		topColorI = m_pStageSettings->inactiveColor;
	}
	else
	{
		topColorI = m_pStageSettings->activeColors[m_ColorState - 1];
	}

	//const Color3i& topColorI = m_IsActive ? m_pArena->GetPrimaryColor() : m_pArena->GetSecondaryColor();
	Color3f topColor = Color3f{ static_cast<float>(topColorI.r) / 255.f,static_cast<float>(topColorI.g) / 255.f,static_cast<float>(topColorI.b) / 255.f };
	const Color3i bottomColorI = m_pStageSettings->inactiveColor;
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

Point2f ArenaTile::GetHexPoint(Point2f center, float size, int i) const
{
	const float angle_deg = 60.f * static_cast<float>(i) - 30.f;
	const float angle_rad = static_cast<float>(M_PI) * angle_deg / 180.f;

	const float posX{ static_cast<float>(center.x) + size * cos(angle_rad) };
	const float posY{ static_cast<float>(center.y) + size * sin(angle_rad) };

	return { posX, posY };
}