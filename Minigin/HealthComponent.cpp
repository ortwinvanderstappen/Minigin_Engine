#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"

HealthComponent::HealthComponent(int startHealth, int maxHealth) :
	m_Health{ startHealth },
	MAX_HEALTH{ maxHealth }
{
}

void HealthComponent::DecreaseHealth(int amount)
{
	m_Health -= amount;
	CheckIfDead();
}

void HealthComponent::SetHealth(int health)
{
	m_Health = health;
	CheckIfDead();
}

int HealthComponent::GetHealth() const
{
	return m_Health;
}

int HealthComponent::GetMaxHealth() const
{
	return MAX_HEALTH;
}

void HealthComponent::Update()
{}

void HealthComponent::CheckIfDead()
{
	if (m_Health <= 0)
	{
		m_Health = 0;
		Notify(*m_pParentObject, Observer::Event::event_player_die);
	}
	else
	{
		Notify(*m_pParentObject, Observer::Event::event_player_lose_life);
	}
}
