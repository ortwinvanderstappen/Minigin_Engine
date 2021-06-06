#include "stdafx.h"
#include "GameArena.h"

#include <GameObject.h>
#include <GameTime.h>
#include <imgui.h>
#include <iostream>
#include <Renderer.h>
#include <Scene.h>
#include <SDL_render.h>
#include <SoundComponent.h>
#include <structs.h>
#include <algorithm>

#include "ArenaTile.h"
#include "Coily.h"
#include "CoilyAIComponent.h"
#include "CompletedTilesObserver.h"
#include "FlyingDisc.h"
#include "HealthObserver.h"
#include "CoilyPlayerControllerAdderObserver.h"
#include "GameContext.h"
#include "PlayerControllerComponent.h"
#include "QBert.h"
#include "RandomAIComponent.h"
#include "ScoreObserver.h"
#include "ScoreRenderComponent.h"
#include "SpawnerComponent.h"
#include "TileMovementComponent.h"
#include "TileRevertCreature.h"
#include "Ugg.h"
#include "Wrongway.h"

GameArena::GameArena(GameManager* pGameManager, GameManager::GameMode gameMode,
	GameManager::StageSettings* const stageSettings, int stage) :
	m_pGameManager(pGameManager),
	m_GameMode(gameMode),
	m_pStageSettings(stageSettings),
	m_Stage(stage),
	m_TileSize(0.f),
	m_TileCount(0),
	m_spHealthObserver(std::make_shared<HealthObserver>(this, stageSettings->lives)),
	m_spCompletedTilesObserver(std::make_shared<CompletedTilesObserver>(this)),
	m_IsStageResetting(false),
	m_StageResetTimer(0.f),
	m_StageResetTime(0.f)
{
	std::cout << "Arena started, lives: " << m_spHealthObserver->GetLives() << "\n";
}

GameArena::~GameArena()
{}

void GameArena::Initialize()
{
	using namespace minigen;
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();
	// Obtain window size
	int width; int height;
	SDL_GetRendererOutputSize(pRenderer, &width, &height);

	const Point2f scorePosition{ static_cast<float>(width) * .7f, 50.f };
	const std::shared_ptr<ScoreRenderComponent> spScoreRenderComponent = std::make_shared<ScoreRenderComponent>(scorePosition);
	GetParent()->AddComponent(spScoreRenderComponent);

	const std::shared_ptr<SoundComponent> spLevelStartSound = std::make_shared<SoundComponent>("Data/audio/LevelStart.wav");
	spLevelStartSound->PlaySoundEffect();

	InitializeArena();
	CreateSpawners();
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
	m_TileSize = static_cast<float>(std::min<int>(width, height)) / static_cast<float>(baseWidth * 2);

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
			m_ArenaHexes[m_ArenaHexes.size() - 1].AddObserver(m_pGameManager->GetScoreObserver());
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

void GameArena::CreateSpawners()
{
	const EntityProperty* pCoilyProperty = GameContext::GetInstance().GetEntityProperty(EntityType::coily);
	const EntityProperty* pSlickSamProperty = GameContext::GetInstance().GetEntityProperty(EntityType::slickOrSam);
	const EntityProperty* pUggProperty = GameContext::GetInstance().GetEntityProperty(EntityType::ugg);
	const EntityProperty* pWrongwayProperty = GameContext::GetInstance().GetEntityProperty(EntityType::wrongway);

	std::shared_ptr<SpawnerComponent> spCoilySpawner = std::make_shared<SpawnerComponent>(pCoilyProperty->minSpawnTime, pCoilyProperty->maxSpawnTime);
	std::shared_ptr<SpawnerComponent> spSlickSamSpawner = std::make_shared<SpawnerComponent>(pSlickSamProperty->minSpawnTime, pSlickSamProperty->maxSpawnTime);
	std::shared_ptr<SpawnerComponent> spUggSpawner = std::make_shared<SpawnerComponent>(pUggProperty->minSpawnTime, pUggProperty->maxSpawnTime);
	std::shared_ptr<SpawnerComponent> spWrongwaySpawner = std::make_shared<SpawnerComponent>(pWrongwayProperty->minSpawnTime, pWrongwayProperty->maxSpawnTime);

	spCoilySpawner->AddSpawnFunction([this]() { SpawnCoily(); });
	spSlickSamSpawner->AddSpawnFunction([this]() { SpawnSlickOrSam(); });
	spUggSpawner->AddSpawnFunction([this]() { SpawnUgg(); });
	spWrongwaySpawner->AddSpawnFunction([this]() { SpawnWrongway(); });

	GetParent()->AddComponent(spCoilySpawner);
	GetParent()->AddComponent(spSlickSamSpawner);
	GetParent()->AddComponent(spUggSpawner);
	GetParent()->AddComponent(spWrongwaySpawner);

	m_spSpawners.push_back(spCoilySpawner);
	m_spSpawners.push_back(spSlickSamSpawner);
	m_spSpawners.push_back(spUggSpawner);
	m_spSpawners.push_back(spWrongwaySpawner);
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

		m_wpFlyingDiscs.push_back(m_spFlyingDisc);
	}
}

void GameArena::Update()
{
	const float deltaTime = Time::GetInstance().GetDeltaTime();

	if (m_IsStageResetting)
	{
		m_StageResetTimer += deltaTime;

		if (m_StageResetTimer > m_StageResetTime)
		{
			m_IsStageResetting = false;

			// Remove all dynamic entities except for the player
			const std::shared_ptr<Coily> coily = m_wpCoily.lock();
			if (coily) coily->GetParent()->MarkForDelete();
			const std::shared_ptr<TileRevertCreature> spSam = m_wpSam.lock();
			if (spSam) spSam->GetParent()->MarkForDelete();
			const std::shared_ptr<TileRevertCreature> spSlick = m_wpSlick.lock();
			if (spSlick) spSlick->GetParent()->MarkForDelete();
			const std::shared_ptr<Ugg> spUgg = m_wpUgg.lock();
			if (spUgg) spUgg->GetParent()->MarkForDelete();
			const std::shared_ptr<Wrongway> spWrongway = m_wpWrongway.lock();
			if (spWrongway) spWrongway->GetParent()->MarkForDelete();

			for (const std::shared_ptr<SpawnerComponent>& spSpawner : m_spSpawners)
			{
				spSpawner->ResetSpawnTimer();
			}
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
	ImGui::Separator();
	ImGui::Text("Stage %i", (m_Stage + 1));
	ImGui::Text("Lives %i", m_spHealthObserver->GetLives());
	ImGui::Separator();
	ImGui::Text("Uncompleted tiles %i", m_TileCount - m_spCompletedTilesObserver->GetCompletedTileCount());
	ImGui::Separator();
	ImGui::End();
}

void GameArena::AddPlayers()
{
	switch (m_GameMode)
	{
	case GameManager::GameMode::Single:
		SpawnPlayer(GetTopTile(), PlayerControllerComponent::HardwareType::Both);
		break;
	case GameManager::GameMode::Duo:
		SpawnPlayer(&m_ArenaHexes[GetBottomLeftTileIndex()], PlayerControllerComponent::HardwareType::Keyboard);
		SpawnPlayer(&m_ArenaHexes[GetBottomRightTileIndex()], PlayerControllerComponent::HardwareType::Controller);
		break;
	case GameManager::GameMode::Versus:
		SpawnPlayer(GetTopTile(), PlayerControllerComponent::HardwareType::Keyboard);
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
	if (m_wpCoily.lock()) return;

	std::shared_ptr<minigen::GameObject> spCoilyObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<Coily> spCoily = std::make_shared<Coily>(this, GetTopTile(), m_spPlayers);
	spCoilyObject->AddComponent(spCoily);
	spCoily->AddObserver(m_pGameManager->GetScoreObserver());
	m_wpCoily = spCoily;

	const float aiWaitTime = GameContext::GetInstance().GetEntityProperty(EntityType::coily)->aiWaitTime;

	if (m_GameMode == GameManager::GameMode::Versus)
	{
		const std::shared_ptr<RandomAIComponent> spRandomAIComponent = std::make_shared<RandomAIComponent>(this, aiWaitTime);
		spCoilyObject->AddComponent(spRandomAIComponent);

		// This component will add the player controller to coily when possible
		const std::shared_ptr<CoilyPlayerControllerAdderObserver> spPlayerControllerAdderObserver = std::make_shared<CoilyPlayerControllerAdderObserver>();
		spCoily->AddObserver(spPlayerControllerAdderObserver);
	}
	else
	{
		// Attach Coily AI component to Coily
		spCoilyObject->AddComponent(std::make_shared<CoilyAIComponent>(this, aiWaitTime));
	}

	m_pParentObject->GetScene()->Add(spCoilyObject);
}

void GameArena::SpawnSlickOrSam()
{
	std::vector<TileRevertCreature::CreatureType> types{};

	if (!m_wpSlick.lock())
		types.push_back(TileRevertCreature::CreatureType::Slick);
	if (!m_wpSam.lock())
		types.push_back(TileRevertCreature::CreatureType::Sam);

	if (types.empty()) return;

	TileRevertCreature::CreatureType type = types[rand() % types.size()];

	std::shared_ptr<minigen::GameObject> spObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<TileRevertCreature> spSlickOrSam = std::make_shared<TileRevertCreature>(this, GetTopTile(), type);
	spObject->AddComponent(spSlickOrSam);
	spSlickOrSam->AddObserver(m_pGameManager->GetScoreObserver());
	GetParent()->GetScene()->Add(spObject);

	switch (type)
	{
	case TileRevertCreature::CreatureType::Slick:
		m_wpSlick = spSlickOrSam;
		break;
	case TileRevertCreature::CreatureType::Sam:
		m_wpSam = spSlickOrSam;
		break;
	default:;
	}
}

void GameArena::SpawnUgg()
{
	if (m_wpUgg.lock()) return;

	std::shared_ptr<minigen::GameObject> spObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<Ugg> spUgg = std::make_shared<Ugg>(this, &m_ArenaHexes[GetBottomRightTileIndex()]);
	spObject->AddComponent(spUgg);
	GetParent()->GetScene()->Add(spObject);

	m_wpUgg = spUgg;
}

void GameArena::SpawnWrongway()
{
	if (m_wpWrongway.lock()) return;

	std::shared_ptr<minigen::GameObject> spObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<Wrongway> spWrongway = std::make_shared<Wrongway>(this, &m_ArenaHexes[GetBottomLeftTileIndex()]);
	spObject->AddComponent(spWrongway);
	GetParent()->GetScene()->Add(spObject);

	m_wpWrongway = spWrongway;
}

void GameArena::Restart() const
{
	m_pGameManager->Restart();
}

void GameArena::HandleLevelCompletion() const
{
	// Calculate how many discs are remaining
	for (const std::weak_ptr<FlyingDisc> wpDisc : m_wpFlyingDiscs)
	{
		const std::shared_ptr<FlyingDisc> spDisc = wpDisc.lock();
		if (spDisc)
		{
			m_pGameManager->GetScoreObserver()->Notify(GetParent(), minigen::Observer::Event::event_remaining_flying_disc);
		}
	}

	m_pGameManager->LoadNextStage();
}

void GameArena::ResetStageEntities(float delay)
{
	m_IsStageResetting = true;
	m_StageResetTime = delay;
	m_StageResetTimer = 0.f;

	for (const std::shared_ptr<SpawnerComponent>& spSpawner : m_spSpawners)
	{
		spSpawner->ResetSpawnTimer();
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
	case TileMovementComponent::MovementType::upRight:
		newIndex = currentIndex + rowLength;
		break;
	case TileMovementComponent::MovementType::downLeft:
		newIndex = currentIndex - (rowLength + 1);
		break;
	case TileMovementComponent::MovementType::upLeft:
		newIndex = currentIndex + rowLength - 1;
		break;
	case TileMovementComponent::MovementType::downRight:
		newIndex = currentIndex - (rowLength + 1) + 1;
		break;
	case TileMovementComponent::MovementType::left:
		newIndex = currentIndex - 1;
		break;
	case TileMovementComponent::MovementType::right:
		newIndex = currentIndex + 1;
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

void GameArena::SpawnPlayer(ArenaTile* pTile, PlayerControllerComponent::HardwareType hardwareType)
{
	std::shared_ptr<minigen::GameObject> qbertObject = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<QBert> qbert = std::make_shared<QBert>(this, pTile);
	qbertObject->AddComponent(qbert);

	qbert->AddObserver(m_spHealthObserver);

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
