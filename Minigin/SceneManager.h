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
		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		void Initialize();
	};
}
