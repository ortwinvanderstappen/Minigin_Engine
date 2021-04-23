#pragma once
#include "Observer.h"

namespace minigen {
	class GameObject;
	class TextRenderComponent;
	class VitalsObserver : public Observer
	{
	public:
		VitalsObserver() = default;

		void Notify(const GameObject& gameObject, Event event) override;
		void AddPlayer(GameObject* pGameObject, std::shared_ptr<TextRenderComponent> spText);

	private:
		struct PlayerVitals
		{
			GameObject* pGameObject = nullptr;
			int health = -1;
			std::shared_ptr<TextRenderComponent> spHealthText{};
		};

		std::vector<PlayerVitals> m_Players{};

		PlayerVitals* GetPlayerVital(const GameObject& gameObject);
	};
}

