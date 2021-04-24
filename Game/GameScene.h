#pragma once
#include <Scene.h>
class GameScene : public minigen::Scene
{
public:
	GameScene(const std::string& sceneName);

	void Initialize() override;

	void Update() override;
};

