#include "GameArena.h"

#include <iostream>
#include <SDL_render.h>

#include "ArenaTile.h"
#include "GameObject.h"
#include "QBert.h"
#include "Renderer.h"
#include "Scene.h"
#include "structs.h"

GameArena::GameArena(const GameScene::StageSettings& stageSettings) :
	m_BaseWidth(stageSettings.size),
	m_PrimaryColor(stageSettings.activeColor),
	m_SecondaryColor(stageSettings.inactiveColor)
{}

GameArena::~GameArena()
{}

void GameArena::Initialize()
{
	InitializeArena();
	AddPlayers();
}

void GameArena::InitializeArena()
{
	using namespace minigen;
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();

	// Obtain window size
	int width; int height;
	SDL_GetRendererOutputSize(pRenderer, &width, &height);

	// Calculate hex size
	const float hexSize = static_cast<float>(std::min(width, height)) / static_cast<float>(m_BaseWidth * 2);

	// Calculate the start position based on hex sizes and screen size
	const float offsetX = static_cast<float>(sqrt(3)) * hexSize;
	const float offsetY = 2 * hexSize;
	const float totalWidthNeeded = offsetX * m_BaseWidth + offsetX * 2;
	const Point2f startPos{ ((static_cast<float>(width) - totalWidthNeeded) / 2.f), static_cast<float>(height) - (offsetY) };
	Point2f currentPos{ startPos };

	int index = 0;

	// Initialize hex grids
	for (int row = 0; row < m_BaseWidth + 2; ++row)
	{
		for (int column = 0; column <= m_BaseWidth + 2; ++column)
		{
			if (!(column - row >= 0)) continue;

			const bool isNullTile = (row == 0 || row == m_BaseWidth + 1) || (column - row == 0 || column == m_BaseWidth + 2);

			ArenaTile hex{ this, index, row, column, hexSize, currentPos, isNullTile };
			m_ArenaHexes.push_back(std::move(hex));
			currentPos.x += offsetX;
			++index;
		}
		// row is done, reset x position
		currentPos.x = startPos.x + (offsetX / 2) * (static_cast<float>(row) + 1.f);
		currentPos.y -= static_cast<float>(offsetY) * .75f;
	}
}

void GameArena::Update()
{}

void GameArena::Render() const
{
	for (const ArenaTile& hex : m_ArenaHexes)
	{
		hex.Render();
	}
}

void GameArena::AddPlayers()
{
	for (int i = 0; i < m_PlayerCount; ++i)
	{
		std::shared_ptr<minigen::GameObject> qbertObject = std::make_shared<minigen::GameObject>();
		const std::shared_ptr<QBert> qbertComponent = std::make_shared<QBert>(i);
		qbertObject->AddScript(qbertComponent);
		m_pParentObject->GetScene()->Add(qbertObject);

		int playerTileIndex;
		if(m_PlayerCount == 1)
		{
			playerTileIndex = GetTopTileIndex();
		} else
		{
			playerTileIndex = i == 0 ? GetBottomLeftTileIndex(): GetBottomRightTileIndex();
		}
		
		qbertComponent->SetTile(&m_ArenaHexes[playerTileIndex]);
	}

}

const Color3i& GameArena::GetPrimaryColor() const
{
	return m_PrimaryColor;
}

const Color3i& GameArena::GetSecondaryColor() const
{
	return m_SecondaryColor;
}

ArenaTile* GameArena::GetNeighbourTile(ArenaTile* pCurrentTile, MovementType movementType)
{
	const int currentIndex = pCurrentTile->GetIndex();
	const int currentRow = pCurrentTile->GetRow();

	int newIndex = -1;

	const int maxHeight = m_BaseWidth + 3;
	const int rowLength = maxHeight - currentRow;

	switch (movementType)
	{
	case MovementType::up:
		newIndex = currentIndex + rowLength;
		break;
	case MovementType::down:
		newIndex = currentIndex - (rowLength + 1);
		break;
	case MovementType::left:
		newIndex = currentIndex + rowLength - 1;
		break;
	case MovementType::right:
		newIndex = currentIndex - (rowLength + 1) + 1;
		break;
	}

	ArenaTile* pTile = nullptr;

	if (newIndex < m_ArenaHexes.size() && newIndex >= 0)
	{
		pTile = &m_ArenaHexes[newIndex];
	}

	return pTile;
}

int GameArena::CalculateArenaHexCount() const
{
	int base = m_BaseWidth;
	int count = 0;
	while (base > 0)
	{
		count += base;
		base -= 1;
	}
	return count;
}

int GameArena::GetTopTileIndex() const
{
	return static_cast<int>(m_ArenaHexes.size()) - 4;
}

int GameArena::GetBottomLeftTileIndex() const
{
	// First 2 is the extra null layers, second 2 is to get the correct position
	return m_BaseWidth + 2 + 2;
}

int GameArena::GetBottomRightTileIndex() const
{
	return GetBottomLeftTileIndex() + m_BaseWidth - 1;
}
