#pragma once
#include "stdafx.h"
#include <vector>

#include "GameManager.h"

class JsonParser
{
public:
	JsonParser() = default;

	void ParseDifficulties(std::vector<GameManager::StageSettings>& outStageSettings);
	void ParseEntityProperties(std::vector<EntityProperty>& outEntityProperties);
};

