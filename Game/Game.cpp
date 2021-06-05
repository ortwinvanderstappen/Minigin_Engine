#include "Game.h"

#include <iostream>
#include <Minigin.h>
#include <SDL_render.h>


#include "Scene.h"
#include "ButtonComponent.h"
#include "CloseGameCommand.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"
#include "InputComponent.h"
#include "OpenGameSceneCommand.h"
#include "Renderer.h"
#include "ScoreRenderComponent.h"

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
	CreateGlobalInputs();
	CreateMenuScene();
	CreateGameScene();
	CreateVictoryScene();
	SceneManager::GetInstance().SetActiveScene("MainMenu");
}

void Game::CreateGlobalInputs() const
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
}

void Game::CreateMenuScene()
{
	const std::shared_ptr<Scene> spMainMenuScene = std::make_shared<Scene>("MainMenu");
	SceneManager::GetInstance().AddScene(spMainMenuScene);

	CreateMenuSceneInput(spMainMenuScene);
	CreateMenuSceneButtons(spMainMenuScene);
}
void Game::CreateMenuSceneInput(const std::shared_ptr<Scene>& spScene) const
{
	std::shared_ptr<GameObject> spInputObject = std::make_shared<GameObject>();
	spScene->Add(spInputObject);

	// HUD input
	const auto openSceneCommand = std::make_shared<OpenGameSceneCommand>();
	auto inputComponent = std::make_shared<InputComponent>();

	InputManager::KeyInput openGameSceneInput{};
	openGameSceneInput.hardwareType = InputManager::HardwareType::controller;
	openGameSceneInput.inputType = InputManager::InputType::onKeyDown;
	openGameSceneInput.spInputCommand = openSceneCommand;
	openGameSceneInput.inputButton.controllerButton = InputManager::ControllerButton::ButtonA;
	inputComponent->AddInput(openGameSceneInput);

	InputManager::KeyInput openGameSceneInput2{};
	openGameSceneInput2.hardwareType = InputManager::HardwareType::keyboard;
	openGameSceneInput2.inputType = InputManager::InputType::onKeyDown;
	openGameSceneInput2.spInputCommand = openSceneCommand;
	openGameSceneInput2.inputButton.keyboardButton = SDL_KeyCode::SDLK_a;
	inputComponent->AddInput(openGameSceneInput2);

	InputManager::KeyInput openGameSceneInput3{};
	openGameSceneInput3.hardwareType = InputManager::HardwareType::keyboard;
	openGameSceneInput3.inputType = InputManager::InputType::onKeyDown;
	openGameSceneInput3.spInputCommand = openSceneCommand;
	openGameSceneInput3.inputButton.keyboardButton = SDL_KeyCode::SDLK_SPACE;
	inputComponent->AddInput(openGameSceneInput3);

	spInputObject->AddComponent(inputComponent);
}
void Game::CreateMenuSceneButtons(const std::shared_ptr<Scene>& spScene)
{
	// Menu buttons
	std::shared_ptr<GameObject> menuObject = std::make_shared<GameObject>();
	spScene->Add(menuObject);

	// Position data
	const Point2f singleButtonPosition{ 510.f, 241.f };
	const Point2f duoButtonPosition{ 510.f, 341.f };
	const Point2f versusButtonPosition{ 510.f, 440.f };

	/// Buttons
	// Single
	Rectf singlePlayColliderRect{ singleButtonPosition.x, singleButtonPosition.y, 765.f - singleButtonPosition.x, 309 - singleButtonPosition.y };
	const std::shared_ptr<ButtonComponent> singlePlayButton = std::make_shared<ButtonComponent>(singlePlayColliderRect);
	menuObject->AddComponent(singlePlayButton);
	auto singleCallback = [this]() { StartGame(GameManager::GameMode::Single); };
	singlePlayButton->SetCallback(singleCallback);
	// Duo
	Rectf duoPlayColliderRect{ duoButtonPosition.x, duoButtonPosition.y, 765.f - duoButtonPosition.x, 408 - duoButtonPosition.y };
	const std::shared_ptr<ButtonComponent> duoPlayButton = std::make_shared<ButtonComponent>(duoPlayColliderRect);
	menuObject->AddComponent(duoPlayButton);
	auto duoCallback = [this]() { StartGame(GameManager::GameMode::Duo); };
	duoPlayButton->SetCallback(duoCallback);
	// Versus
	Rectf versusPlayColliderRect{ versusButtonPosition.x, versusButtonPosition.y, 765.f - versusButtonPosition.x, 505 - versusButtonPosition.y };
	const std::shared_ptr<ButtonComponent> versusPlayButton = std::make_shared<ButtonComponent>(versusPlayColliderRect);
	menuObject->AddComponent(versusPlayButton);
	auto versusCallback = [this]() { StartGame(GameManager::GameMode::Versus); };
	versusPlayButton->SetCallback(versusCallback);

	// Images
	const std::shared_ptr<ImageRenderComponent> singlePlayImage = std::make_shared<ImageRenderComponent>();
	singlePlayImage->AddImage("images/Menu/ButtonSingle.png", Point2f(singleButtonPosition.x, singleButtonPosition.y));
	menuObject->AddComponent(singlePlayImage);
	const std::shared_ptr<ImageRenderComponent> duoPlayImage = std::make_shared<ImageRenderComponent>();
	singlePlayImage->AddImage("images/Menu/ButtonDuo.png", Point2f(duoButtonPosition.x, duoButtonPosition.y));
	menuObject->AddComponent(duoPlayImage);
	const std::shared_ptr<ImageRenderComponent> versusPlayImage = std::make_shared<ImageRenderComponent>();
	singlePlayImage->AddImage("images/Menu/ButtonVersus.png", Point2f(versusButtonPosition.x, versusButtonPosition.y));
	menuObject->AddComponent(versusPlayImage);
}

void Game::StartGame(GameManager::GameMode gameMode) const
{
	std::cout << "Starting game...\n";

	std::shared_ptr<GameManager> spGameManager = m_wpGameManager.lock();
	if (spGameManager)
	{
		spGameManager->StartGame(gameMode);
		SceneManager::GetInstance().SetActiveScene("GameScene");
	}
	else
	{
		std::cerr << "Game: No game manager found!\n";
	}
}

void Game::CreateGameScene()
{
	const auto spGameScene = std::make_shared<Scene>("GameScene");
	SceneManager::GetInstance().AddScene(spGameScene);

	// Create the game manager
	std::shared_ptr<GameObject> spManagerObject = std::make_shared<GameObject>();
	spManagerObject->SetTag("GameManager");
	spGameScene->Add(spManagerObject);
	const std::shared_ptr<GameManager> spGameManager = std::make_shared<GameManager>();
	spManagerObject->AddComponent(spGameManager);
	// Store the game manager
	m_wpGameManager = spGameManager;
}

void Game::CreateVictoryScene() const
{
	const auto spScene = std::make_shared<Scene>("VictoryScene");
	SceneManager::GetInstance().AddScene(spScene);
	CreateVictorySceneButtons(spScene);

	std::shared_ptr<GameObject> spScoreObject = std::make_shared<GameObject>();
	spScoreObject->SetTag("Score");


	using namespace minigen;
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();
	// Obtain window size
	int width; int height;
	SDL_GetRendererOutputSize(pRenderer, &width, &height);

	const Point2f scorePosition{ static_cast<float>(width) * .5f, 215.f };
	const std::shared_ptr<ScoreRenderComponent> spScoreRenderComponent = std::make_shared<ScoreRenderComponent>(scorePosition);
	spScoreObject->AddComponent(spScoreRenderComponent);
	spScene->Add(spScoreObject);
}
void Game::CreateVictorySceneButtons(const std::shared_ptr<Scene>& spScene) const
{
	// Menu buttons
	std::shared_ptr<GameObject> spMenuObject = std::make_shared<GameObject>();
	spScene->Add(spMenuObject);

	const Point2f menuButtonPosition{ 510.f, 341.f };

	// Menu
	Rectf menuPlayColliderRect{ menuButtonPosition.x, menuButtonPosition.y, 765.f - menuButtonPosition.x, 408 - menuButtonPosition.y };
	const std::shared_ptr<ButtonComponent> spMenuButton = std::make_shared<ButtonComponent>(menuPlayColliderRect);
	spMenuObject->AddComponent(spMenuButton);
	auto singleCallback = []() { SceneManager::GetInstance().SetActiveScene("MainMenu"); };
	spMenuButton->SetCallback(singleCallback);

	// Image
	const std::shared_ptr<ImageRenderComponent> spMenuButtonImage = std::make_shared<ImageRenderComponent>();
	spMenuButtonImage->AddImage("images/Menu/ButtonMainMenu.png", Point2f(menuButtonPosition.x, menuButtonPosition.y));
	spMenuObject->AddComponent(spMenuButtonImage);

	// Image
	const std::shared_ptr<ImageRenderComponent> spBeatGameImage = std::make_shared<ImageRenderComponent>();
	spMenuButtonImage->AddImage("images/Menu/GameBeatImage.png", Point2f(428.f, 121.f));
	spMenuObject->AddComponent(spMenuButtonImage);
}
