#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)

#include "ArenaTile.h"
#include "GameScene.h"
#include "structs.h"
#include "TileMovementComponent.h"

class Coily;
class QBert;

class GameArena : public minigen::Script
{
public:
	enum class GameMode
	{
		Single,
		Duo,
		Versus
	};
	
	GameArena(GameMode gameMode, GameScene::StageSettings* const stageSettings, int stage);
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

	GameMode m_GameMode;
	GameScene::StageSettings* m_pStageSettings;
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
