#include "SpawnerComponent.h"
#include "GameTime.h"

SpawnerComponent::SpawnerComponent(float minTimeToSpawn, float maxTimeToSpawn) :
	m_MinTimeToSpawn(minTimeToSpawn),
	m_MaxTimeToSpawn(maxTimeToSpawn),
	m_TimeToSpawn(FLT_MAX),
	m_TimeToSpawnTimer(0.f)
{}

void SpawnerComponent::Initialize()
{
	SetNewRandomSpawnTime();
}

void SpawnerComponent::Update()
{
	const float deltaTime = Time::GetInstance().GetDeltaTime();

	m_TimeToSpawnTimer += deltaTime;
	if (m_TimeToSpawnTimer > m_TimeToSpawn)
	{
		m_TimeToSpawnTimer = 0.f;
		Spawn();
	}
}

void SpawnerComponent::ResetSpawnTimer()
{
	m_TimeToSpawnTimer = 0.f;
}

void SpawnerComponent::AddSpawnFunction(const SpawnFunction& spawnFunction)
{
	m_SpawnFunctions.push_back(spawnFunction);
}

void SpawnerComponent::Spawn()
{
	for (SpawnFunction& spawnFunction : m_SpawnFunctions)
	{
		spawnFunction();
	}

	SetNewRandomSpawnTime();
}

void SpawnerComponent::SetNewRandomSpawnTime()
{
	m_TimeToSpawn = static_cast<float>(fmod(static_cast<double>(rand()), static_cast<double>(m_MaxTimeToSpawn - m_MinTimeToSpawn))) + m_MinTimeToSpawn;
}
