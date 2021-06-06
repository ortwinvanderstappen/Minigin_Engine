#pragma once
#include "stdafx.h"

#include <RenderComponent.h>

#include "ArenaTile.h"
#include "GameManager.h"
#include "PlayerControllerComponent.h"
#include "TileMovementComponent.h"
#include "TileRevertCreature.h"
#include "GameStructs.h"

class SpawnerComponent;
class Wrongway;
class Ugg;
class TileRevertCreature;
class CompletedTilesObserver;
class HealthObserver;
class Coily;
class QBert;

class GameArena : public minigen::RenderComponent
{
public:

	GameArena(GameManager* pGameManager, GameManager::GameMode gameMode, GameManager::StageSettings* const stageSettings, int stage);
	~GameArena() override;

	void Initialize() override;

	void Update() override;
	void Render() const override;

	const std::vector<std::shared_ptr<QBert>>& GetPlayers() const;

	void Restart() const;
	void HandleLevelCompletion() const;
	void ResetStageEntities(float delay = 0.f);

	float GetTileSize() const;
	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, TileMovementComponent::MovementType movement);
	ArenaTile* GetTopTile();
	bool IsBottomTileIndex(int index) const;
private:
	
	void InitializeArena();
	void CreateSpawners();
	void CreateDiscs();

	void AddPlayers();
	void SpawnPlayer(ArenaTile* pTile, PlayerControllerComponent::HardwareType hardwareType);
	
	void SpawnCoily();
	void SpawnSlickOrSam();
	void SpawnUgg();
	void SpawnWrongway();

	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;
	int GetNullTileIndexOnRow(int row, bool isLeft) const;

	GameManager* m_pGameManager;
	GameManager::GameMode m_GameMode;
	GameManager::StageSettings* m_pStageSettings;
	int m_Stage;

	float m_TileSize;
	int m_TileCount;

	std::weak_ptr<Coily> m_wpCoily;
	std::weak_ptr<TileRevertCreature> m_wpSam;
	std::weak_ptr<TileRevertCreature> m_wpSlick;
	std::weak_ptr<Ugg> m_wpUgg;
	std::weak_ptr<Wrongway> m_wpWrongway;
	std::vector<std::weak_ptr<FlyingDisc>> m_wpFlyingDiscs;

	std::vector<ArenaTile> m_ArenaHexes{};
	std::vector<std::shared_ptr<QBert>> m_spPlayers;
	std::shared_ptr<HealthObserver> m_spHealthObserver;
	std::shared_ptr<CompletedTilesObserver> m_spCompletedTilesObserver;

	bool m_IsStageResetting;
	float m_StageResetTimer;
	float m_StageResetTime;
	std::vector<std::shared_ptr<SpawnerComponent>> m_spSpawners;
};
