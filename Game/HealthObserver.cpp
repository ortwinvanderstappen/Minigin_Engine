#include "stdafx.h"
#include "HealthObserver.h"

#include "GameArena.h"

HealthObserver::HealthObserver(GameArena* pArena, int lives) :
	m_pArena(pArena),
	m_Lives(lives)
{}

void HealthObserver::Notify(minigen::GameObject*, Event event)
{
	if (event == Event::event_qbert_death)
	{
		m_Lives -= 1;
		if(m_Lives <= 0)
		{
			m_pArena->Restart();
		} else
		{
			m_pArena->ResetStageEntities();
		}
	}
}

int HealthObserver::GetLives() const
{
	return m_Lives;
}
