#pragma once
#include "stdafx.h"

#include <memory>
#include <Observer.h>

class Coily;
class CoilyPlayerControllerAdderObserver : public minigen::Observer
{
public:
	CoilyPlayerControllerAdderObserver() = default;

	void Notify(minigen::GameObject* pGameObject, Event event) override;

private:
	void AddPlayerController(minigen::GameObject* pGameObject) const;
	std::weak_ptr<Coily> m_wpCoily;
};

