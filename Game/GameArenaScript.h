#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)

#include "ArenaHexScript.h"
#include "GameScene.h"
#include "structs.h"

class GameArenaScript : public minigen::Script
{
public:
	GameArenaScript(const GameScene::StageSettings& stageSettings);
	~GameArenaScript() override;

	void Initialize() override;
	void InitializeArena();
	
	void Update() override;
	void Render() const override;

	void AddPlayer();
	
	const Color3i& GetPrimaryColor() const;
	const Color3i& GetSecondaryColor() const;
private:
	int CalculateArenaHexCount () const;

	std::vector<ArenaHexScript> m_ArenaHexes{};
	
	int m_BaseWidth = -1;
	Color3i m_PrimaryColor{};
	Color3i m_SecondaryColor{};
};
