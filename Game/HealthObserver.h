#pragma once
#include "stdafx.h"

#include <Observer.h>

class GameArena;

class HealthObserver: public minigen::Observer
{
public:
	HealthObserver(GameArena* pArena, int lives);
	
	void Notify(minigen::GameObject* pGameObject, Event event) override;

	int GetLives() const;

private:
	GameArena* m_pArena;
	int m_Lives;
};

