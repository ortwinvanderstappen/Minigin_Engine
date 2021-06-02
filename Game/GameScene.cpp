#include "GameScene.h"
#include <iostream>
#include "FPSComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "GameArenaScript.h"
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

	// Create input object
	auto inputObject = std::make_shared<GameObject>();
	Add(inputObject);

	// Setup input
	auto inputComponent = std::make_shared<InputComponent>();
	InputManager::KeyInput openGameSceneInput{};
	openGameSceneInput.id = 0;
	openGameSceneInput.hardwareType = InputManager::HardwareType::controller;
	openGameSceneInput.inputType = InputManager::InputType::onKeyDown;
	openGameSceneInput.inputButton.controllerButton = InputManager::ControllerButton::ButtonA;
	inputComponent->AddInput(openGameSceneInput);
	inputObject->AddComponent(inputComponent);

	InitializeStage();
}

void GameScene::Update()
{
	Scene::Update();

	if (InputManager::GetInstance().IsInputTriggered(0))
	{
		std::cout << "Input with id 0 is triggered\n";
	}
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
	const auto gameArenaScript = std::make_shared<GameArenaScript>(m_Stages[m_Stage].m_Size);
	gameArenaObject->AddComponent(gameArenaScript);
	Add(gameArenaObject);
}
