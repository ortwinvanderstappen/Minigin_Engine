#include "MiniginPCH.h"
#include "Minigin.h"

#include <chrono>
#include <SDL.h>
#include <thread>
// Audio
#pragma warning(push)
#pragma warning(disable:4244)
#include <audio.c>
#include <audio.h>
#pragma warning(pop)
// Managers
#include "GameTime.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
// Services
#include "ServiceLocator.h"
#include "BasicSoundSystem.h"
#include "LoggingSoundSystem.h"
// ImGui
#include <backends/imgui_impl_sdl.h>

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
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}


	Renderer::GetInstance().Init(m_Window);

	// Register the sound system, each sound system starts their own seperate thread and immediately starts
	const std::shared_ptr<SoundSystem> spDefaultSoundSystem = std::make_shared<BasicSoundSystem>();
	//const std::shared_ptr<SoundSystem> spLoggingSoundSystem = std::make_shared<LoggingSoundSystem>(spDefaultSoundSystem);
	ServiceLocator::RegisterSoundSystem(spDefaultSoundSystem);

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	srand(static_cast<unsigned int>(time(nullptr)));

	m_IsInitialized = true;
	std::cout << "Minigen: Initialize completed\n";
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
	if (!m_IsInitialized)
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
