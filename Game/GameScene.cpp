#include "GameScene.h"
#include <iostream>
#include "FPSComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "GameArenaScript.h"
#include "JsonParser.h"

using namespace minigen;

GameScene::GameScene(const std::string& sceneName) :
	Scene(sceneName),
	m_Stage(0)
{}

void GameScene::Initialize()
{
	UpdateStageSettings();
	
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

	// Setup pyramid game object
	auto gameArenaObject = std::make_shared<GameObject>();
	const auto gameArenaScript = std::make_shared<GameArenaScript>(m_Stages[m_Stage].m_Size);
	gameArenaObject->AddComponent(gameArenaScript);
	Add(gameArenaObject);

	auto fpsObject = std::make_shared<GameObject>();
	const auto fpsComponent = std::make_shared<FPSComponent>();
	fpsObject->AddComponent(fpsComponent);
	Add(fpsObject);

}

void GameScene::Update()
{
	Scene::Update();

	if (InputManager::GetInstance().IsInputTriggered(0))
	{
		std::cout << "Input with id 0 is triggered\n";
	}
}

void GameScene::UpdateStageSettings()
{
	JsonParser jp{};
	jp.ParseDifficulties(m_Stages);
}
