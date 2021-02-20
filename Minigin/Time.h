#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void SetFixedDeltaTime(float newDeltaTime);
	float GetFixedDeltaTime() const;
	const float& FixedDeltaTime() const;
	
	void SetDeltaTime(float newDeltaTime);
	float GetDeltaTime() const;
	const float& DeltaTime() const;
private:
	float m_FixedDeltaTime = 0.f;
	float m_DeltaTime = 0.f;
};

