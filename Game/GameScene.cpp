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
	
	ImGui::Begin("Info", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos(ImVec2{ 0.f,5.f });
	ImGui::Text("FPS: %.1f", static_cast<double>(ImGui::GetIO().Framerate));
	ImGui::Text("Stage %i", m_Stage);
	ImGui::Separator();
	ImGui::End();
}

void GameScene::InitializeStageSettings()
{
	JsonParser jp{};
	jp.ParseDifficulties(m_Stages);
}

void GameScene::InitializeStage()
{
	// Setup pyramid game object
	auto gameArenaObject = std::make_shared<GameObject>();
	Add(gameArenaObject);
	
	const auto gameArenaScript = std::make_shared<GameArena>(m_Stages[m_Stage]);
	gameArenaObject->AddScript(gameArenaScript);
}
