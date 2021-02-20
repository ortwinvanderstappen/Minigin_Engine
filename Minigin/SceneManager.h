#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void FixedUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		void Initialize();
	};
}
