#include "MainMenuScene.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"
#include "ImGuiComponent.h"
#include "InputComponent.h"
#include "OpenGameSceneCommand.h"
#include "TextRenderComponent.h"

MainMenuScene::MainMenuScene(const std::string& sceneName) :
	Scene(sceneName)
{}

void MainMenuScene::Initialize()
{
	using namespace minigen;

	// Create HUD object
	auto HUDGameObject = std::make_shared<GameObject>();
	Add(HUDGameObject);

	auto imguiC = std::make_shared<ImGuiComponent>();
	HUDGameObject->AddComponent(imguiC);

	// Background image
	std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("background.jpg");
	HUDGameObject->AddComponent(imageRenderComponent);

	// Play text
	auto playTextComp = std::make_shared<TextRenderComponent>();
	playTextComp->AddText(0, "Press A or space to start the game", Point2f{ 50.f,50.f }, 30);
	HUDGameObject->AddComponent(playTextComp);

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

	HUDGameObject->AddComponent(inputComponent);
}
