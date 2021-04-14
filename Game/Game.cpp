#include "Game.h"
#include <Minigin.h>


#include "CloseGameCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"
#include "InputComponent.h"
#include "MainMenuScene.h"
#include "TextRenderComponent.h"

using namespace minigen;

void Game::Run()
{
	Minigin engine{};
	engine.Initialize();
	LoadGame();
	engine.Run();
}

void Game::LoadGame()
{
	// Setup global inputs
	InputManager& inputManager = InputManager::GetInstance();
	// Close game with controller
	const std::shared_ptr<CloseGameCommand> closeGameCommand = std::make_shared<CloseGameCommand>();
	InputManager::KeyInput closeGameInputController;
	closeGameInputController.spInputCommand = closeGameCommand;
	closeGameInputController.hardwareType = InputManager::HardwareType::controller;
	closeGameInputController.inputType = InputManager::InputType::onKeyDown;
	closeGameInputController.inputButton.controllerButton = InputManager::ControllerButton::BackButton;
	inputManager.AddGlobalInput(closeGameInputController);
	// Close game with keyboard
	InputManager::KeyInput closeGameInputKeyboard;
	closeGameInputKeyboard.spInputCommand = closeGameCommand;
	closeGameInputKeyboard.hardwareType = InputManager::HardwareType::keyboard;
	closeGameInputKeyboard.inputType = InputManager::InputType::onKeyDown;
	closeGameInputKeyboard.inputButton.keyboardButton = SDL_KeyCode::SDLK_ESCAPE;
	inputManager.AddGlobalInput(closeGameInputKeyboard);
	
	CreateMenuScene();
	CreateGameScene();
	SceneManager::GetInstance().SetActiveScene("MainMenu");
}

void Game::CreateMenuScene()
{
	std::shared_ptr<MainMenuScene> mainMenuScene = std::make_shared<MainMenuScene>("MainMenu");
	SceneManager::GetInstance().AddScene(mainMenuScene);
}

void Game::CreateGameScene()
{
	Scene& gameScene = SceneManager::GetInstance().CreateScene("Game");
	// Create a background
	auto go = std::make_shared<GameObject>();
	std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("logo.png");
	go->AddComponent(imageRenderComponent);
	gameScene.Add(go);
}
