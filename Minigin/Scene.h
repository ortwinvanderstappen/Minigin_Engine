#pragma once
#include <functional>

#include "SceneManager.h"

namespace minigen
{
	class GameObject;
	class Scene final
	{
		typedef std::function<void()> EmptyFunctionCallback;

		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		explicit Scene(const std::string& name);

		void Add(const std::shared_ptr<GameObject>& object);
		const std::vector<std::shared_ptr<GameObject>>& GetObjects() const;

		void Update();
		void Render() const;

		const std::string& GetName() const;

		void Initialize() {};
		void OnSceneEnter() { if (m_OnSceneEnterCallback) m_OnSceneEnterCallback(); };
		void OnSceneLeave() { if (m_OnSceneLeaveCallback) m_OnSceneLeaveCallback(); };

		void SetOnSceneEnterCallback(EmptyFunctionCallback callback);
		void SetOnSceneLeaveCallback(EmptyFunctionCallback callback);

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		std::vector <std::shared_ptr<GameObject>> m_Objects{};

	private:
		std::string m_Name;
		static unsigned int m_IdCounter;
		bool m_DrawDebugColliders;

		EmptyFunctionCallback m_OnSceneEnterCallback;
		EmptyFunctionCallback m_OnSceneLeaveCallback;
	};

}
