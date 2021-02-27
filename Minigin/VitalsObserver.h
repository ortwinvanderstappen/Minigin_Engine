#pragma once
#include "Observer.h"

class dae::GameObject;
class TextRenderComponent;
class VitalsObserver : public Observer
{
public:
	VitalsObserver() = default;

	void Notify(const dae::GameObject& gameObject, Event event) override;
	void AddPlayer(dae::GameObject* pGameObject, std::shared_ptr<TextRenderComponent> spText);

private:
	struct PlayerVitals
	{
		dae::GameObject* pGameObject = nullptr;
		int health = -1;
		std::shared_ptr<TextRenderComponent> spHealthText{};
	};
	
	std::vector<PlayerVitals> m_Players{};

	PlayerVitals* GetPlayerVital(const dae::GameObject& gameObject);
};

