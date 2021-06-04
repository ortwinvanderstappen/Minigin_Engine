#include "GameScene.h"
#include <iostream>
#include "FPSComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "GameArena.h"
#include "ImGuiComponent.h"
#include "JsonParser.h"

using namespace minigen;

GameScene::GameScene(const std::string& sceneName) :
	Scene(sceneName),
	m_Stage(0)
{}

void GameScene::Initialize()
{
	InitializeStageSettings();
	InitializeStage();
}

void GameScene::Update()
{
	Scene::Update();
}

void GameScene::Render() const
{
	Scene::Render();
}

void GameScene::Restart()
{
	m_Stage = 0;
	InitializeStage();
}

void GameScene::InitializeStageSettings()
{
	JsonParser jp{};
	jp.ParseDifficulties(m_Stages);
}

void GameScene::InitializeStage()
{
	for (const std::shared_ptr<GameObject>& object : m_Objects)
	{
		object->MarkForDelete();
	}

	// Setup pyramid game object
	std::shared_ptr<GameObject> spArena = std::make_shared<GameObject>();
	Add(spArena);

	const auto gameArenaScript = std::make_shared<GameArena>(GameArena::GameMode::Single, &m_Stages[m_Stage], m_Stage);
	spArena->AddComponent(gameArenaScript);

	std::cout << "Stage started, objects: " << m_Objects.size();
	std::cout << "...\n";
}

void GameScene::LoadNextStage()
{
	if (m_Stage < m_Stages.size() - 1)
	{
		++m_Stage;
		InitializeStage();
	}
	else
	{
		std::cout << "VICTORY!\n";
	}
}
