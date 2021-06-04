#pragma once
#include "RenderComponent.h"
#include "ArenaTile.h"
#include "GameManager.h"
#include "TileMovementComponent.h"

class Coily;
class QBert;

class GameArena : public minigen::RenderComponent
{
public:
	
	GameArena(GameManager* pGameManager, GameManager::GameMode gameMode, GameManager::StageSettings* const stageSettings, int stage);
	~GameArena() override;

	void Initialize() override;
	void InitializeArena();
	void CreateDiscs();

	void Update() override;
	void Render() const override;

	void AddPlayers();
	const std::vector<std::shared_ptr<QBert>>& GetPlayers() const;

	void SpawnCoily();

	void HandleQbertDeath();
	void HandleLevelCompletion() const;

	void ResetStageEntities();
	void IncreaseCompletedTiles(int change);

	float GetTileSize() const;
	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, TileMovementComponent::MovementType movement);
	ArenaTile* GetTopTile();
	bool IsBottomTileIndex(int index) const;
private:
	void SpawnPlayer(ArenaTile* pTile, bool useController);
	
	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;
	int GetNullTileIndexOnRow(int row, bool isLeft) const;

	GameManager* m_pGameManager;
	GameManager::GameMode m_GameMode;
	GameManager::StageSettings* m_pStageSettings;
	int m_Stage;
	int m_Lives;
	
	float m_TileSize;
	int m_TileCount;
	int m_CompletedTiles;
	float m_CoilySpawnTime;
	float m_CoilySpawnTimer;
	std::weak_ptr<Coily> m_wpCoily;

	std::vector<ArenaTile> m_ArenaHexes{};
	std::vector<std::shared_ptr<QBert>> m_spPlayers;
};
