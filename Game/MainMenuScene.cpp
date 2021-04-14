#include "MainMenuScene.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"
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

	// Background image
	std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("background.jpg");
	HUDGameObject->AddComponent(imageRenderComponent);

	// Play text
	auto playTextComp = std::make_shared<TextRenderComponent>();
	playTextComp->AddText(0, "Press A to start the game", Point2f{ 50.f,50.f }, 30);
	HUDGameObject->AddComponent(playTextComp);

	// HUD input
	auto inputComponent = std::make_shared<InputComponent>();
	InputManager::KeyInput openGameSceneInput;
	openGameSceneInput.hardwareType = InputManager::HardwareType::controller;
	openGameSceneInput.inputType = InputManager::InputType::onKeyDown;
	openGameSceneInput.spInputCommand = std::make_shared<OpenGameSceneCommand>();
	openGameSceneInput.inputButton.controllerButton = InputManager::ControllerButton::ButtonA;
	inputComponent->AddInput(openGameSceneInput);
	HUDGameObject->AddComponent(inputComponent);
}
