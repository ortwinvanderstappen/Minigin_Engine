#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>
// Managers
#include "ResourceManager.h"
#include "CommandManager.h"
#include "InputManager.h"
#include "SceneManager.h"
// Objects
#include "GameObject.h"
#include "TextObject.h"

#include "Renderer.h"
#include "Scene.h"
#include "Time.h"
// Components
#include "ImageRenderComponent.h"
#include "HealthComponent.h"
#include "ImGuiComponent.h"
#include "FPSComponent.h"
#include "ObserverManager.h"
#include "SuicideCommand.h"
#include "VitalsObserver.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

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
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	std::shared_ptr<ImageRenderComponent> imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("background.jpg");
	go->AddComponent(imageRenderComponent);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	imageRenderComponent = std::make_shared<ImageRenderComponent>();
	imageRenderComponent->AddImage("logo.png");
	go->AddComponent(imageRenderComponent);
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	std::shared_ptr<TextRenderComponent> to = std::make_shared<TextRenderComponent>();
	to->AddText(0, "Programming 4 Assignment", { 0,0 }, 36);
	go->AddComponent(to);
	go->SetPosition(80, 20);
	scene.Add(go);

	// Create vitals observer
	std::shared_ptr<VitalsObserver> spVitalsObserver {std::make_shared<VitalsObserver>()};
	ObserverManager::GetInstance().AddObserver(spVitalsObserver);

	// Create fps game object
	std::shared_ptr<GameObject> spFPSGameObject = std::make_shared<GameObject>();
	std::shared_ptr<FPSComponent> spFPSComponent{ std::make_shared<FPSComponent>() };
	spFPSGameObject->AddComponent(spFPSComponent);
	scene.Add(spFPSGameObject);
	
	// Create QBert gameobject
	const int startHealth{ 1 };
	const int maxHealth{ 3 };
	std::shared_ptr<GameObject> spQBert{ std::make_shared<GameObject>() };
	// Health component
	std::shared_ptr<HealthComponent> spHealthComponent{ std::make_shared<HealthComponent>( startHealth, maxHealth) };
	spHealthComponent->AddObserver(spVitalsObserver);
	spQBert->AddComponent(spHealthComponent);
	// Health text component
	std::shared_ptr<TextRenderComponent> spPlayerHealthTextComponent{std::make_shared<TextRenderComponent>()};
	spQBert->AddComponent(spPlayerHealthTextComponent);
	spPlayerHealthTextComponent->AddText(0, "Player life: " + std::to_string(spHealthComponent->GetHealth()), Point2f{0, 70}, 30);
	// Add to scene
	scene.Add(spQBert);
	// Add player to vital observer
	spVitalsObserver->AddPlayer(spQBert.get(), spPlayerHealthTextComponent);
	m_Players.push_back(spQBert);

	// Create QBert 2 gameobject
	std::shared_ptr<GameObject> spQBert2{ std::make_shared<GameObject>() };
	// Health component
	std::shared_ptr<HealthComponent> spHealthComponent2{ std::make_shared<HealthComponent>( startHealth, maxHealth) };
	spHealthComponent2->AddObserver(spVitalsObserver);
	spQBert2->AddComponent(spHealthComponent2);
	// Health text component
	std::shared_ptr<TextRenderComponent> spPlayerHealthTextComponent2{std::make_shared<TextRenderComponent>()};
	spQBert2->AddComponent(spPlayerHealthTextComponent2);
	spPlayerHealthTextComponent2->AddText(0, "Player life: " + std::to_string(spHealthComponent2->GetHealth()), Point2f{0, 120}, 30);
	// Add to scene
	scene.Add(spQBert2);
	// Add player to vital observer
	spVitalsObserver->AddPlayer(spQBert2.get(), spPlayerHealthTextComponent2);
	m_Players.push_back(spQBert2);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	// Setup the demo scene
	LoadGame();

	auto& input = InputManager::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& time = Time::GetInstance();

	if (m_Players.size() >= 1)
	{
		std::shared_ptr<SuicideCommand> spSuicideCommand{ std::make_shared<SuicideCommand>(m_Players[0]) };
		input.BindInput(ControllerButton::ButtonA, spSuicideCommand);
	}

	if(m_Players.size() >= 2)
	{
		std::shared_ptr<SuicideCommand> spSuicideCommand{ std::make_shared<SuicideCommand>(m_Players[1]) };
		input.BindInput(ControllerButton::ButtonB, spSuicideCommand);
	}

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
