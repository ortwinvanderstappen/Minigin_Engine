#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)

#include "ArenaTile.h"
#include "GameScene.h"
#include "structs.h"

class GameArena : public minigen::Script
{
public:
	enum class MovementType
	{
		up,
		down,
		left,
		right
	};
	
	GameArena(GameScene::StageSettings* const stageSettings);
	~GameArena() override;

	void Initialize() override;
	void InitializeArena();
	void CreateDiscs();
	
	void Update() override;
	void Render() const override;

	void AddPlayers();
	
	const Color3i& GetPrimaryColor() const;
	const Color3i& GetSecondaryColor() const;

	float GetTileSize() const;

	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, MovementType movementType);
	ArenaTile* GetTopTile();
private:
	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;
	int GetNullTileIndexOnRow(int row, bool isLeft) const;

	std::vector<ArenaTile> m_ArenaHexes{};
	int m_PlayerCount = 1;

	GameScene::StageSettings* m_pStageSettings;
	float m_TileSize;
};
