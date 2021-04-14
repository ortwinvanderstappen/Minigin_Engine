#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>
// Audio
#pragma warning(push)
#pragma warning(disable:4244)
#include "audio.h"
#include "audio.c"
#pragma warning(pop)
// Managers
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
// Objects
#include "GameObject.h"
#include "TextObject.h"

#include "Renderer.h"
#include "Scene.h"
#include "GameTime.h"
// Components
#include "ImageRenderComponent.h"
#include "HealthComponent.h"
#include "ImGuiComponent.h"
#include "FPSComponent.h"
#include "ObserverManager.h"
#include "SuicideCommand.h"
#include "VitalsObserver.h"
// Services
#include "ServiceLocator.h"

// Temp
#include "BasicSoundSystem.h"
#include "ChangeSoundSystemCommand.h"
#include "LoggingSoundSystem.h"
#include "PlaySoundCommand.h"

// Github repo: https://github.com/ortwinvanderstappen/Minigin_Engine

using namespace std;
using namespace std::chrono;

void minigen::Minigin::Initialize()
{
	if (_putenv("SDL_AUDIODRIVER=directsound") != 0)
	{
		throw std::runtime_error(std::string("Failed to set audio driver"));
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	initAudio();

	m_Window = SDL_CreateWindow(
		"Minigen - Ortwin Van der Stappen",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	// Register the sound system, each sound system starts their own seperate thread and immediately starts
	const std::shared_ptr<SoundSystem> spDefaultSoundSystem = std::make_shared<BasicSoundSystem>();
	ServiceLocator::RegisterSoundSystem(spDefaultSoundSystem);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	m_IsInitialized = true;
	std::cout << "Minigen: Initialize completed\n";
}

void minigen::Minigin::LoadGame()
{
	//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//auto go = std::make_shared<GameObject>();
	//std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	//imageRenderComponent->AddImage("background.jpg");
	//go->AddComponent(imageRenderComponent);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//imageRenderComponent = std::make_shared<ImageRenderComponent>();
	//imageRenderComponent->AddImage("logo.png");
	//go->AddComponent(imageRenderComponent);
	//go->SetPosition(216, 180);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//std::shared_ptr<TextRenderComponent> to = std::make_shared<TextRenderComponent>();
	//to->AddText(0, "Programming 4 Assignment", { 0,0 }, 36);
	//std::shared_ptr<TextRenderComponent> to2 = std::make_shared<TextRenderComponent>();
	//to2->AddText(0, "Press X (xbox) for sound", { -75,350 }, 36);
	//std::shared_ptr<TextRenderComponent> to3 = std::make_shared<TextRenderComponent>();
	//to3->AddText(0, "Press Y (xbox) to swap sound system", { -75,400 }, 36);
	//go->AddComponent(to);
	//go->AddComponent(to2);
	//go->AddComponent(to3);
	//go->SetPosition(80, 20);
	//scene.Add(go);

	//// Create vitals observer
	//std::shared_ptr<VitalsObserver> spVitalsObserver{ std::make_shared<VitalsObserver>() };
	//ObserverManager::GetInstance().AddObserver(spVitalsObserver);

	//// Create fps game object
	//std::shared_ptr<GameObject> spFPSGameObject = std::make_shared<GameObject>();
	//std::shared_ptr<FPSComponent> spFPSComponent{ std::make_shared<FPSComponent>() };
	//spFPSGameObject->AddComponent(spFPSComponent);
	//scene.Add(spFPSGameObject);

	//// Create QBert gameobject
	//const int startHealth{ 1 };
	//const int maxHealth{ 3 };
	//std::shared_ptr<GameObject> spQBert{ std::make_shared<GameObject>() };
	//// Health component
	//std::shared_ptr<HealthComponent> spHealthComponent{ std::make_shared<HealthComponent>(startHealth, maxHealth) };
	//spHealthComponent->AddObserver(spVitalsObserver);
	//spQBert->AddComponent(spHealthComponent);
	//// Health text component
	//std::shared_ptr<TextRenderComponent> spPlayerHealthTextComponent{ std::make_shared<TextRenderComponent>() };
	//spQBert->AddComponent(spPlayerHealthTextComponent);
	//spPlayerHealthTextComponent->AddText(0, "(Controller A) Player life: " + std::to_string(spHealthComponent->GetHealth()), Point2f{ 0, 70 }, 30);
	//// Add to scene
	//scene.Add(spQBert);
	//// Add player to vital observer
	//spVitalsObserver->AddPlayer(spQBert.get(), spPlayerHealthTextComponent);
	//m_Players.push_back(spQBert);

	//// Create QBert 2 gameobject
	//std::shared_ptr<GameObject> spQBert2{ std::make_shared<GameObject>() };
	//// Health component
	//std::shared_ptr<HealthComponent> spHealthComponent2{ std::make_shared<HealthComponent>(startHealth, maxHealth) };
	//spHealthComponent2->AddObserver(spVitalsObserver);
	//spQBert2->AddComponent(spHealthComponent2);
	//// Health text component
	//std::shared_ptr<TextRenderComponent> spPlayerHealthTextComponent2{ std::make_shared<TextRenderComponent>() };
	//spQBert2->AddComponent(spPlayerHealthTextComponent2);
	//spPlayerHealthTextComponent2->AddText(0, "(Controller B) Player life: " + std::to_string(spHealthComponent2->GetHealth()), Point2f{ 0, 120 }, 30);
	//// Add to scene
	//scene.Add(spQBert2);
	//// Add player to vital observer
	//spVitalsObserver->AddPlayer(spQBert2.get(), spPlayerHealthTextComponent2);
	//m_Players.push_back(spQBert2);

	//auto& input = InputManager::GetInstance();
	//if (m_Players.size() >= 1)
	//{
	//	std::shared_ptr<SuicideCommand> spSuicideCommand{ std::make_shared<SuicideCommand>(m_Players[0]) };
	//	input.BindInput(ControllerButton::ButtonA, spSuicideCommand);
	//}

	//if (m_Players.size() >= 2)
	//{
	//	std::shared_ptr<SuicideCommand> spSuicideCommand{ std::make_shared<SuicideCommand>(m_Players[1]) };
	//	input.BindInput(ControllerButton::ButtonB, spSuicideCommand);
	//}

	//// Create sound input (for testing)
	//const std::shared_ptr<PlaySoundCommand> spPlaySoundCommand{ std::make_shared<PlaySoundCommand>("../Data/audio/Menu_Tick.wav") };
	//input.AddInput(ControllerButton::ButtonX, InputManager::InputType::onKeyDown);
	//input.BindInput(ControllerButton::ButtonX, spPlaySoundCommand);

	//const std::shared_ptr<ChangeSoundSystemCommand> spChangeSoundSystemCommand{ std::make_shared<ChangeSoundSystemCommand>() };
	//input.AddInput(ControllerButton::ButtonY, InputManager::InputType::onKeyDown);
	//input.BindInput(ControllerButton::ButtonY, spChangeSoundSystemCommand);

	std::cout << "Minigen: LoadGame completed\n";
}

void minigen::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	endAudio();
	SDL_Quit();
}

void minigen::Minigin::Run()
{
	if(!m_IsInitialized)
	{
		std::cout << "Minigen: ERROR, Minigen was not initialized!\n";
		return;
	}
	std::cout << "Minigen: Game loop started\n";
	
	auto& input = InputManager::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = Time::GetInstance();

	auto lastTime = high_resolution_clock::now();
	bool doContinue = true;

	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		float const deltaTime = duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		time.SetDeltaTime(deltaTime);

		doContinue = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();

		const auto sleepTime = currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now();
		this_thread::sleep_for(sleepTime);
	}

	Cleanup();
}
