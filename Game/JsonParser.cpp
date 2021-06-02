#include "JsonParser.h"

#include <iostream>
#include "JsonReader.h"
#include "rapidjson.h"
#include "filereadstream.h"
#include "stream.h"

void JsonParser::ParseDifficulties(std::vector<GameScene::StageSettings>& stageSettings)
{
	using rapidjson::Value;
	
	JsonReader jr{};
	rapidjson::Document* jsonDoc = jr.ReadJson("../Data/game_difficulties.json");

	const Value& difficultyObject = (*jsonDoc)["levels"];
	// Loop through each level entry
	for (Value::ConstValueIterator valueIt = difficultyObject.Begin(); valueIt != difficultyObject.End(); ++valueIt)
	{
		// Obtain values
		const Value& levelValue = *valueIt;
		const Value& sizeValue = levelValue["size"];

		// Create stage entry
		GameScene::StageSettings stage{};

		// Setup properties
		stage.m_Size = sizeValue.GetInt();

		// Add to list
		stageSettings.push_back(stage);
	}
}
