#include "Game.h"
#include <Minigin.h>

#include "SceneManager.h"

void Game::Run()
{
	minigen::Minigin engine;
	engine.Initialize();
	LoadGame();
	engine.Run();
}

void Game::LoadGame()
{
	CreateMenuScene();
	CreateGameScene();
}

void Game::CreateMenuScene()
{
	minigen::Scene& scene = minigen::SceneManager::GetInstance().CreateScene("MainMenu");
}

void Game::CreateGameScene()
{
	minigen::Scene& scene = minigen::SceneManager::GetInstance().CreateScene("Game");
}
