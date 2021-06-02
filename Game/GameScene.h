#pragma once
#include <Scene.h>
#include <vector>
class GameScene : public minigen::Scene
{
public:
	struct StageSettings
	{
		int m_Size;
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

