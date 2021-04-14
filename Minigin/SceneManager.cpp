#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void minigen::SceneManager::Update() const
{
	if (m_spActiveScene)
	{
		m_spActiveScene->Update();
	}
}

void minigen::SceneManager::Render() const
{

	if (m_spActiveScene)
	{
		m_spActiveScene->Render();
	}
}

minigen::SceneManager::SceneManager()
{
}

void minigen::SceneManager::AddScene(std::shared_ptr<Scene> newScene)
{
	m_Scenes.push_back(newScene);
	newScene->Initialize();
}

minigen::Scene& minigen::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	scene->Initialize();

	if (m_spActiveScene == nullptr)
	{
		m_spActiveScene = scene;
	}

	return *scene;
}

void minigen::SceneManager::SetActiveScene(const std::string& name)
{
	std::shared_ptr<Scene> spScene = nullptr;

	for (const auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			spScene = scene;
			break;
		}
	}

	if (spScene != nullptr)
		m_spActiveScene = spScene;
	else
		std::cout << "SceneManager: ERROR, scene with name " << name << " does not exist\n";
}
