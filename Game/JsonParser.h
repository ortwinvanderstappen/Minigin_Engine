#pragma once
#include <vector>
#include "GameScene.h"

class JsonParser
{
public:
	JsonParser() = default;

	void ParseDifficulties(std::vector<GameScene::StageSettings>& stageSettings);
};

