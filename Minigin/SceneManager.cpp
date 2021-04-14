#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void minigen::SceneManager::Update()
{
	for (auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void minigen::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

minigen::SceneManager::SceneManager()
{
	Initialize();
}

void minigen::SceneManager::Initialize()
{}

minigen::Scene& minigen::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
