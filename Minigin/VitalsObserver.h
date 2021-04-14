#pragma once
#include "Observer.h"

class GameObject;
class TextRenderComponent;
class VitalsObserver : public Observer
{
public:
	VitalsObserver() = default;

	void Notify(const minigen::GameObject& gameObject, Event event) override;
	void AddPlayer(minigen::GameObject* pGameObject, std::shared_ptr<TextRenderComponent> spText);

private:
	struct PlayerVitals
	{
		minigen::GameObject* pGameObject = nullptr;
		int health = -1;
		std::shared_ptr<TextRenderComponent> spHealthText{};
	};
	
	std::vector<PlayerVitals> m_Players{};

	PlayerVitals* GetPlayerVital(const minigen::GameObject& gameObject);
};

