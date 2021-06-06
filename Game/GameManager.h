#pragma once
#include "stdafx.h"

#include <Component.h>
#include <memory>
#include <structs.h>
#include <vector>

#include "GameStructs.h"

namespace minigen {
	class SoundComponent;
}

class ScoreObserver;

class GameManager : public minigen::Component
{
public:
	enum class GameMode
	{
		Single,
		Duo,
		Versus
	};
	
	struct Disc
	{
		int row;
		bool isLeft;
	};
	
	struct StageSettings
	{
		int size;
		int lives;
		bool cyclesColor;
		std::vector<Color3i> activeColors;
		Color3i inactiveColor;
		std::vector<Disc> discs;
	};
	
	GameManager();
	
	void Update() override;
	void Initialize() override;
	void StartGame(GameMode gameMode);
	
	void Restart();
	void LoadNextStage();

	int GetScore() const;

	const std::shared_ptr<ScoreObserver>& GetScoreObserver() const;

private:
	void InitializeStageSettings();
	void InitializeAudio();
	void InitializeStage();
	
	GameMode m_GameMode;
	int m_Stage;
	std::vector<StageSettings> m_Stages;
	
	std::shared_ptr<ScoreObserver> m_spScoreObserver;

	std::shared_ptr<minigen::SoundComponent> m_spLevelBeatSound;
	std::shared_ptr<minigen::SoundComponent> m_spGameBeatSound;
};

