#pragma once
#include <Scene.h>
#include <vector>
#include "structs.h"

class GameScene final: public minigen::Scene
{
public:
	struct Disc
	{
		int row;
		bool isLeft;
	};
	
	struct StageSettings
	{
		int size;
		Color3i activeColor;
		Color3i inactiveColor;

		std::vector<Disc> discs;
	};

	GameScene(const std::string& sceneName);

	void Initialize() override;

	void Update() override;
	void Render() const override;
private:
	void InitializeStageSettings();
	void InitializeStage();

	int m_Stage;
	std::vector<StageSettings> m_Stages;
};

