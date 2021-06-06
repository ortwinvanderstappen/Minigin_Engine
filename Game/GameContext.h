#pragma once
#include "stdafx.h"

#include <memory>
#include <Singleton.h>
#include <vector>

#include "GameStructs.h"

class ScoreObserver;

class GameContext : public minigen::Singleton<GameContext>
{
public:
	void SetScoreObserver(const std::shared_ptr<ScoreObserver>& spScoreObserver);
	const std::shared_ptr<ScoreObserver>& GetScoreObserver() const;

	void SetEntityProperties(const std::vector<EntityProperty>& entityProperties);
	const std::vector<EntityProperty>& GetEntityProperties() const;
	const EntityProperty* GetEntityProperty(EntityType type) const;

private:
	std::shared_ptr<ScoreObserver> m_spScoreObserver;
	std::vector<EntityProperty> m_EntityProperties;
};

