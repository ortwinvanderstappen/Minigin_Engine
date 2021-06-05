#include "GameManager.h"

#include <iostream>


#include "GameObject.h"
#include "JsonParser.h"
#include "GameArena.h"
#include "Scene.h"
#include "ScoreObserver.h"

using namespace minigen;

GameManager::GameManager() :
	m_GameMode(GameMode::Single),
	m_Stage(0),
	m_Stages(),
	m_spScoreObserver(std::make_shared<ScoreObserver>())
{}

void GameManager::Update()
{}

void GameManager::Initialize()
{
	InitializeStageSettings();

	auto onSceneEnter = [this]() { InitializeStage(); };
	GetParent()->GetScene()->SetOnSceneEnterCallback(onSceneEnter);
}

void GameManager::InitializeStageSettings()
{
	JsonParser jp{};
	jp.ParseDifficulties(m_Stages);
}

void GameManager::InitializeStage()
{
	// Remove old stage objects
	std::cout << "Init stage\n";
	int index{ 0 };
	for (const std::shared_ptr<GameObject>& spObject : GetParent()->GetScene()->GetObjects())
	{
		// Don't mark the game manager;
		if (spObject->GetTag() == "GameManager") continue;

		std::cout << "Deleting object with index: " << index << "\n";
		spObject->MarkForDelete();
		++index;
	}

	// Setup pyramid game object
	std::shared_ptr<GameObject> spArena = std::make_shared<GameObject>();
	GetParent()->GetScene()->Add(spArena);

	const auto gameArenaScript = std::make_shared<GameArena>(this, m_GameMode, &m_Stages[m_Stage], m_Stage);
	spArena->AddComponent(gameArenaScript);
}

void GameManager::SetGameMode(GameMode gameMode)
{
	m_GameMode = gameMode;
}

void GameManager::Restart()
{
	m_Stage = 0;
	m_spScoreObserver->ResetScore();
	InitializeStage();
}

void GameManager::LoadNextStage()
{
	if (m_Stage < static_cast<int>(m_Stages.size()) - 1)
	{
		++m_Stage;
		InitializeStage();
	}
	else
	{
		// TODO: Win
	}
}

int GameManager::GetScore() const
{
	return m_spScoreObserver->GetScore();
}

const std::shared_ptr<ScoreObserver>& GameManager::GetScoreObserver() const
{
	return m_spScoreObserver;
}
