#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void SetDeltaTime(float newDeltaTime);
	float GetDeltaTime() const;
	const float& DeltaTime() const;
private:
	float m_DeltaTime = 0.f;
};

