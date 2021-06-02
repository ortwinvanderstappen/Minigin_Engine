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
	
	GameArena(const GameScene::StageSettings& stageSettings);
	~GameArena() override;

	void Initialize() override;
	void InitializeArena();
	
	void Update() override;
	void Render() const override;

	void AddPlayers();
	
	const Color3i& GetPrimaryColor() const;
	const Color3i& GetSecondaryColor() const;

	ArenaTile* GetNeighbourTile(ArenaTile* pCurrentTile, MovementType movementType);
private:
	int CalculateArenaHexCount () const;
	int GetTopTileIndex() const;
	int GetBottomLeftTileIndex() const;
	int GetBottomRightTileIndex() const;

	std::vector<ArenaTile> m_ArenaHexes{};
	int m_PlayerCount = 1;
	
	int m_BaseWidth = -1;
	Color3i m_PrimaryColor{};
	Color3i m_SecondaryColor{};
};
