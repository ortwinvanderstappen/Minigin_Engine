#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include <string>

namespace minigen
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(std::shared_ptr<Scene> newScene);
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		
		void Update() const;
		void Render() const;
	private:
		friend class Singleton<SceneManager>;
		SceneManager();

		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_spActiveScene;
	};
}
