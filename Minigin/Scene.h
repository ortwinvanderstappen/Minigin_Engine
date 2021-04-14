#pragma once
#include "SceneManager.h"

namespace minigen
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		virtual void Add(const std::shared_ptr<GameObject>& object);

		virtual void Update();
		virtual void Render() const;

		virtual const std::string& GetName();
		
		virtual void Initialize(){};

		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		explicit Scene(const std::string& name);

	private:
		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter;
	};

}
