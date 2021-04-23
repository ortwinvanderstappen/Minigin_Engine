#include "MiniginPCH.h"
#include "VitalsObserver.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "TextRenderComponent.h"

void minigen::VitalsObserver::Notify(const minigen::GameObject& gameObject, Event event)
{
	PlayerVitals* pv = GetPlayerVital(gameObject);

	switch (event)
	{
	case Event::event_player_die:
		if (pv)
		{
			pv->spHealthText->SetText(0, "Player died");
		}
		break;
	case Event::event_player_lose_life:
		if (pv)
		{
			auto healthComponent = pv->pGameObject->GetComponent<HealthComponent>();
			if (healthComponent)
			{
				pv->health = healthComponent->GetHealth();
			}
			pv->spHealthText->SetText(0, "Health: " + std::to_string(pv->health));
		}
		break;
	}

	UNREFERENCED_PARAMETER(gameObject);
}

void minigen::VitalsObserver::AddPlayer(minigen::GameObject* pGameObject, std::shared_ptr<TextRenderComponent> spText)
{
	PlayerVitals pv{};
	pv.pGameObject = pGameObject;

	auto healthComponent = pGameObject->GetComponent<HealthComponent>();
	if (healthComponent)
	{
		pv.health = healthComponent->GetHealth();
	}

	pv.spHealthText = spText;

	m_Players.push_back(pv);
}

minigen::VitalsObserver::PlayerVitals* minigen::VitalsObserver::GetPlayerVital(const minigen::GameObject& gameObject)
{
	for (PlayerVitals& pv : m_Players)
	{
		if (pv.pGameObject == &gameObject)
		{
			return &pv;
		}
	}

	return nullptr;
}
