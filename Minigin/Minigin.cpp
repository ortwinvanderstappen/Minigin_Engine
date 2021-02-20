#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "FPSComponent.h"
#include "ImageRenderComponent.h"
#include "CommandManager.h"

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
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto imageRenderComponent = std::make_shared<ImageRenderComponent>();
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
	auto to = std::make_shared<TextRenderComponent>();
	to->AddText(0, "Programming 4 Assignment", { 0,0 }, 36);
	go->AddComponent(to);
	go->SetPosition(80, 20);
	scene.Add(go);

	// Create fps game object
	std::shared_ptr<GameObject> spFPSGameObject = std::make_shared<GameObject>();
	// Create components
	auto spFPSComponent = std::make_shared<FPSComponent>(Point2f{ 0.f,0.f });
	// Add object components
	spFPSGameObject->AddComponent(spFPSComponent);
	// Add object to the scene
	scene.Add(spFPSGameObject);
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

	LoadGame();

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
