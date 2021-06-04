#pragma once
#include <memory>

#include "GameManager.h"

class GameManager;

namespace minigen {
	class Scene;
}

class Game
{
public:
	Game() = default;

	void Run();
private:
	void LoadGame();
	void CreateGlobalInputs() const;

	// Menu
	void CreateMenuScene();
	void CreateMenuSceneInput(const std::shared_ptr<minigen::Scene>& spScene) const;
	void CreateMenuSceneButtons(const std::shared_ptr<minigen::Scene>& spScene);
	void StartGame(GameManager::GameMode gameMode) const;
	// Game
	void CreateGameScene();

	std::weak_ptr<GameManager> m_wpGameManager;
};

