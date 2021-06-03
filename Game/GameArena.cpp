#include "GameArena.h"

#include <iostream>
#include <SDL_render.h>

#include "ArenaTile.h"
#include "FlyingDisc.h"
#include "GameObject.h"
#include "QBert.h"
#include "Renderer.h"
#include "Scene.h"
#include "structs.h"
#include "TileMovementComponent.h"

GameArena::GameArena(GameScene::StageSettings* const stageSettings, int stage) :
	m_pStageSettings(stageSettings),
	m_Stage(stage),
	m_TileSize(0.f),
	m_Lives(stageSettings->lives)
{}

GameArena::~GameArena()
{}

void GameArena::Initialize()
{
	InitializeArena();
	CreateDiscs();
	AddPlayers();
}

void GameArena::InitializeArena()
{
	using namespace minigen;
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();

	// Obtain window size
	int width; int height;
	SDL_GetRendererOutputSize(pRenderer, &width, &height);

	const int baseWidth = m_pStageSettings->size;

	// Calculate hex size
	m_TileSize = static_cast<float>(std::min(width, height)) / static_cast<float>(baseWidth * 2);

	// Calculate the start position based on hex sizes and screen size
	const float offsetX = static_cast<float>(sqrt(3)) * m_TileSize;
	const float offsetY = 2 * m_TileSize;
	const float totalWidthNeeded = offsetX * static_cast<float>(baseWidth) + offsetX * 2;
	const Point2f startPos{ ((static_cast<float>(width) - totalWidthNeeded) / 2.f), static_cast<float>(height) * .95f };
	Point2f currentPos{ startPos };

	int index = 0;

	// Initialize hex grids
	for (int row = 0; row < baseWidth + 2; ++row)
	{
		for (int column = 0; column <= baseWidth + 2; ++column)
		{
			if (!(column - row >= 0)) continue;

			const bool isNullTile = (row == 0 || row == baseWidth + 1) || (column - row == 0 || column == baseWidth + 2);

			ArenaTile hex{ this, index, m_TileSize, currentPos, isNullTile, m_pStageSettings };
			m_ArenaHexes.push_back(std::move(hex));
			currentPos.x += offsetX;
			++index;
		}
		// row is done, reset x position
		currentPos.x = startPos.x + (offsetX / 2) * (static_cast<float>(row) + 1.f);
		currentPos.y -= static_cast<float>(offsetY) * .75f;
	}
}

void GameArena::CreateDiscs()
{
	for (GameScene::Disc disc : m_pStageSettings->discs)
	{
		const int tileIndex = GetNullTileIndexOnRow(disc.row, disc.isLeft);

		if (tileIndex >= static_cast<int>(m_ArenaHexes.size()))
		{
			std::cerr << "GameArena: Attempting to spawn a disc on non existing row!\n";
			return;
		}

		ArenaTile* pTile = &m_ArenaHexes[tileIndex];

		// Make sure parent object is a seperate gameobject
		std::shared_ptr<minigen::GameObject> spDiscObject = std::make_shared<minigen::GameObject>();
		// Spawn the disc and attach it to the null tile
		const std::shared_ptr<FlyingDisc> m_spFlyingDisc = std::make_shared<FlyingDisc>(this, pTile);
		spDiscObject->AddScript(m_spFlyingDisc);
		pTile->AttachFlyingDisc(m_spFlyingDisc);
		// Correctly position the disc
		m_spFlyingDisc->SetPosition(m_ArenaHexes[tileIndex].GetCenter());

		m_pParentObject->GetScene()->Add(spDiscObject);
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

	ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2{ 0.f,5.f });
	ImGui::Text("FPS: %.1f", static_cast<double>(ImGui::GetIO().Framerate));
	ImGui::Text("Stage %i", (m_Stage+1));
	ImGui::Text("Lives %i", m_Lives);
	ImGui::Separator();
	ImGui::End();
}

void GameArena::AddPlayers()
{
	for (int i = 0; i < m_PlayerCount; ++i)
	{
		std::shared_ptr<minigen::GameObject> qbertObject = std::make_shared<minigen::GameObject>();

		int playerTileIndex;
		if (m_PlayerCount == 1)
		{
			playerTileIndex = GetTopTileIndex();
		}
		else
		{
			playerTileIndex = i == 0 ? GetBottomLeftTileIndex() : GetBottomRightTileIndex();
		}

		const std::shared_ptr<QBert> qbert = std::make_shared<QBert>(this, &m_ArenaHexes[playerTileIndex], i);
		qbertObject->AddScript(qbert);
		m_pParentObject->GetScene()->Add(qbertObject);

		m_spPlayers.push_back(qbert);
	}

}

void GameArena::HandleQbertDeath()
{
	m_Lives -= 1;
	ResetStageEntities();

	if(m_Lives <= 0)
	{
		GameScene* pGameScene = dynamic_cast<GameScene*>(m_pParentObject->GetScene());
		if(pGameScene)
		{
			pGameScene->Restart();
		}
	}
}

void GameArena::ResetStageEntities()
{
	// Remove all dynamic entities except for the player

	// Respawn players
	if(m_spPlayers.size() == 1)
	{
		std::shared_ptr<TileMovementComponent> spTMC = m_spPlayers[0]->GetComponent<TileMovementComponent>();
		if(spTMC)
		{
			spTMC->SetTile(GetTopTile());
		}
	}
}

float GameArena::GetTileSize() const
{
	return m_TileSize;
}

ArenaTile* GameArena::GetNeighbourTile(ArenaTile* pCurrentTile, TileMovementComponent::MovementType movement)
{
	const int currentIndex = pCurrentTile->GetIndex();

	int newIndex = -1;

	const int remappedIndex = abs(static_cast<int>(m_ArenaHexes.size() - 1)) - currentIndex;
	// https://en.wikipedia.org/wiki/Triangular_number
	const int row = (m_pStageSettings->size + 2) - static_cast<int>(-1 + sqrt(1 + 8 * remappedIndex)) / 2;

	const int maxHeight = m_pStageSettings->size + 3;
	const int rowLength = maxHeight - row;
	switch (movement)
	{
	case TileMovementComponent::MovementType::up:
		newIndex = currentIndex + rowLength;
		break;
	case TileMovementComponent::MovementType::down:
		newIndex = currentIndex - (rowLength + 1);
		break;
	case TileMovementComponent::MovementType::left:
		newIndex = currentIndex + rowLength - 1;
		break;
	case TileMovementComponent::MovementType::right:
		newIndex = currentIndex - (rowLength + 1) + 1;
		break;
	}

	ArenaTile* pTile = nullptr;

	if (newIndex < static_cast<int>(m_ArenaHexes.size()) && newIndex >= 0)
	{
		pTile = &m_ArenaHexes[newIndex];
	}

	return pTile;
}

ArenaTile* GameArena::GetTopTile()
{
	return &m_ArenaHexes[GetTopTileIndex()];
}

int GameArena::GetTopTileIndex() const
{
	return static_cast<int>(m_ArenaHexes.size()) - 4;
}

int GameArena::GetBottomLeftTileIndex() const
{
	// First 2 is the extra null layers, second 2 is to get the correct position
	return m_pStageSettings->size + 2 + 2;
}

int GameArena::GetBottomRightTileIndex() const
{
	return GetBottomLeftTileIndex() + m_pStageSettings->size - 1;
}

int GameArena::GetNullTileIndexOnRow(int row, bool isLeft) const
{
	int width = m_pStageSettings->size + 3;

	int index{ 0 };
	for (int i = 0; i < row; ++i)
	{
		index += width;
		--width;
	}

	return isLeft ? index : index + (width - 1);
}
