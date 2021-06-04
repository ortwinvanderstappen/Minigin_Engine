#include "MainMenuScene.h"

#include <iostream>

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
	std::shared_ptr<GameObject> HUDGameObject = std::make_shared<GameObject>();
	Add(HUDGameObject);

	// Background image
	std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("background.jpg");
	HUDGameObject->AddComponent(imageRenderComponent);

	std::shared_ptr<ImageRenderComponent> testc = std::make_shared<ImageRenderComponent>();
	testc->AddImage("logo.png", { 0.f,0.f});
	HUDGameObject->AddComponent(testc);

	auto textc = std::make_shared<TextRenderComponent>();
	textc->AddText(0, "Hello test", {50.f, 350.f}, 20);
	HUDGameObject->AddComponent(textc);

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

void MainMenuScene::Update()
{
	Scene::Update();
	
	//Point2i mousePos;
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//std::cout << "mousepos: [ " << mousePos.x << ", " << mousePos.y <<" ] \n";
}
