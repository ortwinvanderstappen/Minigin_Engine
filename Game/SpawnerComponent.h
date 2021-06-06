#pragma once
#include "stdafx.h"

#include <Component.h>
#include <functional>
#include <vector>

class SpawnerComponent : public minigen::Component
{
public:
	typedef std::function<void ()> SpawnFunction;
	
	SpawnerComponent(float minTimeToSpawn, float maxTimeToSpawn);

	void Initialize() override;

	void Update() override;

	void ResetSpawnTimer();
	void AddSpawnFunction(const SpawnFunction& spawnFunction);

private:
	void Spawn();
	void SetNewRandomSpawnTime();
	float m_MinTimeToSpawn;
	float m_MaxTimeToSpawn;
	float m_TimeToSpawn;
	float m_TimeToSpawnTimer;

	std::vector<SpawnFunction> m_SpawnFunctions;
};

