#include "stdafx.h"
#include "JsonParser.h"

#include <iostream>
#include <JsonReader.h>

void JsonParser::ParseDifficulties(std::vector<GameManager::StageSettings>& outStageSettings)
{
	using rapidjson::Value;

	JsonReader jr{};
	rapidjson::Document* jsonDoc = jr.ReadJson("Data/game_difficulties.json");

	const Value& difficultyObject = (*jsonDoc)["levels"];
	// Loop through each level entry
	for (Value::ConstValueIterator valueIt = difficultyObject.Begin(); valueIt != difficultyObject.End(); ++valueIt)
	{
		// Create stage entry
		GameManager::StageSettings stage{};

		// Basic properties
		const Value& levelValue = *valueIt;
		const Value& sizeValue = levelValue["size"];
		const Value& livesValue = levelValue["lives"];
		const Value& cyclesColorValue = levelValue["cyclesColor"];

		// Setup properties
		stage.size = sizeValue.GetInt();
		stage.lives = livesValue.GetInt();
		stage.cyclesColor = cyclesColorValue.GetBool();

		// Active color
		const Value& activeColorsValue = levelValue["activeColors"];
		for (Value::ConstValueIterator activeColorProperty = activeColorsValue.Begin(); activeColorProperty != activeColorsValue.End(); ++activeColorProperty)
		{
			const Value& activeColorValue = *activeColorProperty;
			const Value& activeColorRValue = activeColorValue["r"];
			const Value& activeColorGValue = activeColorValue["g"];
			const Value& activeColorBValue = activeColorValue["b"];
			stage.activeColors.push_back(Color3i{ activeColorRValue.GetInt(), activeColorGValue.GetInt(), activeColorBValue.GetInt() });
		}

		// Inactive color
		const Value& inactiveColorValue = levelValue["inactiveColor"];
		const Value& inactiveColorRValue = inactiveColorValue["r"];
		const Value& inactiveColorGValue = inactiveColorValue["g"];
		const Value& inactiveColorBValue = inactiveColorValue["b"];
		stage.inactiveColor = Color3i{ inactiveColorRValue.GetInt(), inactiveColorGValue.GetInt(), inactiveColorBValue.GetInt() };

		// Discs
		const Value& discsValue = levelValue["discs"];
		for (Value::ConstValueIterator discProperty = discsValue.Begin(); discProperty != discsValue.End(); ++discProperty)
		{
			const Value& discValue = *discProperty;
			const Value& rowValue = discValue["row"];
			const Value& positionValue = discValue["position"];

			const int row = rowValue.GetInt() + 1;
			const int discPosition = positionValue.GetInt();

			switch (discPosition)
			{
			case 1:
			{
				GameManager::Disc disc{};
				disc.row = row;
				disc.isLeft = true;
				stage.discs.push_back(disc);
				break;
			}
			case 2:
			{
				GameManager::Disc disc{};
				disc.row = row;
				disc.isLeft = false;
				stage.discs.push_back(disc);
				break;
			}
			case 3:
			{
				GameManager::Disc discL{};
				discL.row = row;
				discL.isLeft = true;
				GameManager::Disc discR{};
				discR.row = row;
				discR.isLeft = false;
				stage.discs.push_back(discL);
				stage.discs.push_back(discR);
				break;
			}
			}
		}

		// Add to list
		outStageSettings.push_back(stage);
	}
}

void JsonParser::ParseEntityProperties(std::vector<EntityProperty>& outEntityProperties)
{
	using rapidjson::Value;

	JsonReader jr{};
	rapidjson::Document* jsonDoc = jr.ReadJson("Data/entity_properties.json");
	const Value& object = (*jsonDoc);

	for (Value::ConstValueIterator valueIt = object.Begin(); valueIt != object.End(); ++valueIt)
	{
		const Value& entityProperty = *valueIt;

		const Value& nameValue = entityProperty["name"];
		const Value& movespeedValue = entityProperty["movespeed"];
		const Value& minSpawnTimeValue = entityProperty["minSpawnTime"];
		const Value& maxSpawnTimeValue = entityProperty["maxSpawnTime"];
		const Value& aiWaitTimeValue = entityProperty["aiWaitTime"];

		const std::string name = nameValue.GetString();
		const float movespeed = movespeedValue.GetFloat();
		const float minSpawnTime = minSpawnTimeValue.GetFloat();
		const float maxSpawnTime = maxSpawnTimeValue.GetFloat();
		const float aiWaitTime = aiWaitTimeValue.GetFloat();

		EntityProperty property{};

		if (name == "QBert")
			property.entityType = EntityType::qbert;
		else if (name == "Coily")
			property.entityType = EntityType::coily;
		else if (name == "SlickOrSam")
			property.entityType = EntityType::slickOrSam;
		else if (name == "Ugg")
			property.entityType = EntityType::ugg;
		else if (name == "Wrongway")
			property.entityType = EntityType::wrongway;

		property.movespeed = movespeed;
		property.minSpawnTime = minSpawnTime;
		property.maxSpawnTime = maxSpawnTime;
		property.aiWaitTime = aiWaitTime;

		outEntityProperties.push_back(std::move(property));
	}
}
