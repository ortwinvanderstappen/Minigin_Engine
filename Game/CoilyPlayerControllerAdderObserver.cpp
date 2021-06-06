#include "stdafx.h"
#include "CoilyPlayerControllerAdderObserver.h"

#include <algorithm>
#include <memory>

#include "Coily.h"
#include "PlayerControllerComponent.h"
#include "RandomAIComponent.h"

void CoilyPlayerControllerAdderObserver::Notify(minigen::GameObject* pGameObject, Event event)
{
	switch (event)
	{
	case Event::event_coily_transform:
		AddPlayerController(pGameObject);
		break;
	default:;
	}
}

void CoilyPlayerControllerAdderObserver::AddPlayerController(minigen::GameObject* pGameObject) const
{
	// Attach player controller to gameobject
	const std::shared_ptr<PlayerControllerComponent> spPlayerController = std::make_shared<PlayerControllerComponent>(PlayerControllerComponent::HardwareType::Controller);
	pGameObject->AddComponent(spPlayerController);
	pGameObject->RemoveComponent<RandomAIComponent>();
}
