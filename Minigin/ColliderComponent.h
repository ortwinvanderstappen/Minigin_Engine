#pragma once
#include "Component.h"
#include "structs.h"

class ColliderComponent : public minigen::Component
{
public:
	ColliderComponent(const Rectf& boundaries);
	void Update() override;

private:
	Rectf m_Boundaries;
};

