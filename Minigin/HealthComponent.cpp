#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"

minigen::HealthComponent::HealthComponent(int startHealth, int maxHealth) :
	m_Health{ startHealth },
	MAX_HEALTH{ maxHealth }
{
}

void minigen::HealthComponent::DecreaseHealth(int amount)
{
	m_Health -= amount;
	CheckIfDead();
}

void minigen::HealthComponent::SetHealth(int health)
{
	m_Health = health;
	CheckIfDead();
}

int minigen::HealthComponent::GetHealth() const
{
	return m_Health;
}

int minigen::HealthComponent::GetMaxHealth() const
{
	return MAX_HEALTH;
}

void minigen::HealthComponent::Update()
{}

void minigen::HealthComponent::CheckIfDead()
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
