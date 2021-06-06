#include "stdafx.h"
#include "GameContext.h"

#include <iostream>

void GameContext::SetScoreObserver(const std::shared_ptr<ScoreObserver>& spScoreObserver)
{
	m_spScoreObserver = spScoreObserver;
}

const std::shared_ptr<ScoreObserver>& GameContext::GetScoreObserver() const
{
	return m_spScoreObserver;
}

void GameContext::SetEntityProperties(const std::vector<EntityProperty>& entityProperties)
{
	m_EntityProperties = entityProperties;
}

const std::vector<EntityProperty>& GameContext::GetEntityProperties() const
{
	return m_EntityProperties;
}

const EntityProperty* GameContext::GetEntityProperty(EntityType type) const
{
	for (const EntityProperty& prop : m_EntityProperties)
	{
		if (prop.entityType == type)
			return &prop;
	}

	std::cerr << "GameContext: Entity property not found!\n";
	return nullptr;
}
