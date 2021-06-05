#include "GameArena.h"

#include <iostream>
#include <SDL_render.h>

#include "Renderer.h"
#include "Scene.h"
#include "ArenaTile.h"
#include "Coily.h"
#include "CoilyAIComponent.h"
#include "CompletedTilesObserver.h"
#include "FlyingDisc.h"
#include "GameObject.h"
#include "GameTime.h"
#include "PlayerControllerComponent.h"
#include "QBert.h"
#include "structs.h"
#include "TileMovementComponent.h"
#include "HealthObserver.h"
#include "ScoreObserver.h"

GameArena::GameArena(GameManager* pGameManager, GameManager::GameMode gameMode,
	GameManager::StageSettings* const stageSettings, int stage) :
	m_pGameManager(pGameManager),
	m_GameMode(gameMode),
	m_pStageSettings(stageSettings),
	m_Stage(stage),
	m_TileSize(0.f),
	m_TileCount(0),
	m_CoilySpawnTime(3.0f),
	m_CoilySpawnTimer(0.f),
	m_spHealthObserver(std::make_shared<HealthObserver>(this, stageSettings->lives)),
	m_spCompletedTilesObserver(std::make_shared<CompletedTilesObserver>(this))
{
	std::cout << "Arena started, lives: " << m_spHealthObserver->GetLives() << "\n";
}

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
			m_ArenaHexes[m_ArenaHexes.size() - 1].AddObserver(m_spCompletedTilesObserver);
			currentPos.x += offsetX;
			++index;
		}
		// row is done, reset x position
		currentPos.x = startPos.x + (offsetX / 2) * (static_cast<float>(row) + 1.f);
		currentPos.y -= static_cast<float>(offsetY) * .75f;
	}

	for (int i = m_pStageSettings->size; i > 0; --i)
	{
		m_TileCount += i;
	}
	m_spCompletedTilesObserver->SetTileCount(m_TileCount);

}

void GameArena::CreateDiscs()
{
	for (GameManager::Disc disc : m_pStageSettings->discs)
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
		spDiscObject->AddComponent(m_spFlyingDisc);
		pTile->AttachFlyingDisc(m_spFlyingDisc);
		// Correctly position the disc
		m_spFlyingDisc->SetPosition(m_ArenaHexes[tileIndex].GetCenter());

		m_pParentObject->GetScene()->Add(spDiscObject);
	}
}

void GameArena::Update()
{
	const float deltaTime = Time::GetInstance().DeltaTime();

	if (!m_wpCoily.lock())
	{
		if (m_CoilySpawnTimer < m_CoilySpawnTime)
		{
			m_CoilySpawnTimer += deltaTime;
		}
		else
		{
			SpawnCoily();
			m_CoilySpawnTimer -= m_CoilySpawnTime;
		}
	}
}

void GameArena::Render() const
{
	for (const ArenaTile& hex : m_ArenaHexes)
	{
		hex.Render();
	}

	ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2{ 0.f,5.f });
	ImGui::Text("FPS: %.1f", static_cast<double>(ImGui::GetIO().Framerate));
	ImGui::Text("Stage %i", (m_Stage + 1));
	ImGui::Text("Lives %i", m_spHealthObserver->GetLives());
	ImGui::Text("Score %i", m_pGameManager->GetScore());
	ImGui::Text("Completed tiles %i", m_spCompletedTilesObserver->GetCompletedTileCount());
	ImGui::Text("Uncompleted tiles %i", m_TileCount - m_spCompletedTilesObserver->GetCompletedTileCount());
	ImGui::Separator();
	ImGui::End();
}

void GameArena::AddPlayers()
{
	std::cout << "Spawning players...\n";

	switch (m_GameMode)
	{
	case GameManager::GameMode::Single:
		SpawnPlayer(GetTopTile(), false);
		break;
	case GameManager::GameMode::Duo:
		SpawnPlayer(&m_ArenaHexes[GetBottomLeftTileIndex()], false);
		SpawnPlayer(&m_ArenaHexes[GetBottomRightTileIndex()], true);
		break;
	case GameManager::GameMode::Versus:
		SpawnPlayer(GetTopTile(), false);
		break;
	default:;
	}
}

const std::vector<std::shared_ptr<QBert>>& GameArena::GetPlayers() const
{
	return m_spPlayers;
}

void GameArena::SpawnCoily()
{
	std::shared_ptr<minigen::GameObject> spCoilyObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<Coily> spCoily = std::make_shared<Coily>(this, GetTopTile(), m_spPlayers);
	spCoilyObject->AddComponent(spCoily);
	spCoily->AddObserver(m_pGameManager->GetScoreObserver());

	m_wpCoily = spCoily;

	if (m_GameMode == GameManager::GameMode::Versus)
	{
		// Attach player controller to Coily
		PlayerControllerComponent::HardwareType hardwareType = PlayerControllerComponent::HardwareType::Controller;
		const std::shared_ptr<PlayerControllerComponent> playerController = std::make_shared<PlayerControllerComponent>(hardwareType);
		spCoilyObject->AddComponent(playerController);
	}
	else
	{
		// Attach Coily AI component to Coily
		spCoilyObject->AddComponent(std::make_shared<CoilyAIComponent>(this));
	}

	m_pParentObject->GetScene()->Add(spCoilyObject);
}

//void GameArena::HandleQbertDeath()
//{
//	std::cout << "Ouch you died! new lives: " << m_Lives << "\n";
//	ResetStageEntities();
//
//	if (m_Lives <= 0)
//	{
//		m_pGameManager->Restart();
//	}
//}

void GameArena::Restart() const
{
	m_pGameManager->Restart();
}

void GameArena::HandleLevelCompletion() const
{
	m_pGameManager->LoadNextStage();
}

void GameArena::ResetStageEntities()
{
	// Remove all dynamic entities except for the player

	std::shared_ptr<Coily> coily = m_wpCoily.lock();
	if (coily)
	{
		coily->GetParent()->MarkForDelete();
		coily = nullptr;
	}

	//// Set player positions
	//if (m_spPlayers.size() == 1)
	//{
	//	std::shared_ptr<TileMovementComponent> spTMC = m_spPlayers[0]->GetComponent<TileMovementComponent>();
	//	if (spTMC)
	//	{
	//		ArenaTile* pLastTile = spTMC->GetTile();
	//		if (pLastTile && pLastTile->IsNullTile())
	//			spTMC->SetTile(GetTopTile());
	//	}
	//}
}

float GameArena::GetTileSize() const
{
	return m_TileSize;
}

//void GameArena::IncreaseCompletedTiles(int change)
//{
//	m_CompletedTiles += change;
//	if (m_CompletedTiles == m_TileCount)
//	{
//		HandleLevelCompletion();
//	}
//}

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

bool GameArena::IsBottomTileIndex(int index) const
{
	// Example, size 7
	// First row has 10 indices (+2 because bigger null row), (+1 because pyramid)
	// This means it goes until index 9 (size + 2)
	// Second row adds (10 - 1) entries -> 9 + 9  (max index == 18)
	// 18 is a null index so we use < instead of <=

	return index < (m_pStageSettings->size + 2) * 2;
}

void GameArena::SpawnPlayer(ArenaTile* pTile, bool useController)
{
	std::shared_ptr<minigen::GameObject> qbertObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<QBert> qbert = std::make_shared<QBert>(this, pTile);
	qbertObject->AddComponent(qbert);

	qbert->AddObserver(m_spHealthObserver);
	qbert->AddObserver(m_pGameManager->GetScoreObserver());

	// Setup player controller
	PlayerControllerComponent::HardwareType hardwareType = PlayerControllerComponent::HardwareType::Keyboard;
	if (useController)
		hardwareType = PlayerControllerComponent::HardwareType::Controller;

	const std::shared_ptr<PlayerControllerComponent> playerController = std::make_shared<PlayerControllerComponent>(hardwareType);
	qbertObject->AddComponent(playerController);

	m_pParentObject->GetScene()->Add(qbertObject);
	m_spPlayers.push_back(qbert);
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
