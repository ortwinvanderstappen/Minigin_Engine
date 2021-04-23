#pragma once

class Game
{
public:
	Game() = default;

	void Run();
private:
	void LoadGame();
	void CreateMenuScene() const;
	void CreateGameScene() const;
};

