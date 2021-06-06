#include "stdafx.h"
#include "GameManager.h"

#include <GameObject.h>
#include <Scene.h>
#include <SoundComponent.h>

#include "GameArena.h"
#include "GameContext.h"
#include "JsonParser.h"
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
	GameContext::GetInstance().SetScoreObserver(m_spScoreObserver);
	
	InitializeStageSettings();
	InitializeAudio();

	auto onSceneEnter = [this]() { InitializeStage(); };
	GetParent()->GetScene()->SetOnSceneEnterCallback(onSceneEnter);

	//GetParent()->AddComponent(m_spScoreObserver);
}

void GameManager::InitializeStageSettings()
{
	JsonParser jp{};
	jp.ParseDifficulties(m_Stages);
}

void GameManager::InitializeAudio()
{
	m_spLevelBeatSound = std::make_shared<SoundComponent>("Data/audio/LevelBeat.wav");
	GetParent()->AddComponent(m_spLevelBeatSound);
	m_spGameBeatSound = std::make_shared<SoundComponent>("Data/audio/LevelBeat.wav");
	GetParent()->AddComponent(m_spGameBeatSound);
}

void GameManager::InitializeStage()
{
	// Remove old stage objects
	for (const std::shared_ptr<GameObject>& spObject : GetParent()->GetScene()->GetObjects())
	{
		// Don't mark the game manager;
		if (spObject->GetTag() == "GameManager") continue;
		spObject->MarkForDelete();
	}

	// Setup pyramid game object
	std::shared_ptr<GameObject> spArena = std::make_shared<GameObject>();
	GetParent()->GetScene()->Add(spArena);

	const auto gameArenaScript = std::make_shared<GameArena>(this, m_GameMode, &m_Stages[m_Stage], m_Stage);
	spArena->AddComponent(gameArenaScript);
}

void GameManager::StartGame(GameMode gameMode)
{
	m_Stage = 0;
	m_GameMode = gameMode;
	m_spScoreObserver->ResetScore();
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
		m_spLevelBeatSound->PlaySoundEffect();
	}
	else
	{
		m_spGameBeatSound->PlaySoundEffect();
		SceneManager::GetInstance().SetActiveScene("VictoryScene");
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
