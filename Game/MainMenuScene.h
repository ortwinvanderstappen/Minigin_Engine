#pragma once
#include <Scene.h>
class MainMenuScene final: public minigen::Scene
{
public:
	MainMenuScene(const std::string& sceneName);

private:
	void Initialize() override;
public:
	void Update() override;
};

