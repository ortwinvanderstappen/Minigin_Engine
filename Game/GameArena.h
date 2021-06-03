#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)

#include "ArenaTile.h"
#include "GameScene.h"
#include "structs.h"
#include "TileMovementComponent.h"

class QBert;

class GameArena : public minigen::Script
{
public:
	GameArena(GameScene::StageSettings* const stageSettings, int stage);
	~GameArena() override;

	void Initialize() override;
	void InitializeArena();
	void CreateDiscs();

	void Update() override;
	void Render() const override;

	void AddPlayers();
	void HandleQbertDeath();
	void ResetStageEntities();

	float GetTileSize() const;

	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, TileMovementComponent::MovementType movement);
	ArenaTile* GetTopTile();
private:
	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;
	int GetNullTileIndexOnRow(int row, bool isLeft) const;

	std::vector<ArenaTile> m_ArenaHexes{};
	int m_PlayerCount = 1;
	int m_Lives;

	GameScene::StageSettings* m_pStageSettings;
	int m_Stage;
	float m_TileSize;

	std::vector<std::shared_ptr<QBert>> m_spPlayers;
};
