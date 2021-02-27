#pragma once
#include "Component.h"
class HealthComponent : public Component
{
public:
	HealthComponent(int startHealth, int maxHealth);

	void DecreaseHealth(int amount = 1);
	void SetHealth(int health);
	int GetHealth() const;
	int GetMaxHealth() const;

	void Update() override;
	void CheckIfDead();

private:
	int MAX_HEALTH;
	int m_Health;
};

