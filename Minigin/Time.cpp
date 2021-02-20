#include "MiniginPCH.h"
#include "Time.h"

void Time::SetFixedDeltaTime(float newDeltaTime)
{
	m_FixedDeltaTime = newDeltaTime;
}

float Time::GetFixedDeltaTime() const
{
	return m_FixedDeltaTime;
}

const float& Time::FixedDeltaTime() const
{
	return m_FixedDeltaTime;
}

const float& Time::DeltaTime() const
{
	return m_DeltaTime;
}

void Time::SetDeltaTime(float newDeltaTime)
{
	m_DeltaTime = newDeltaTime;
}

float Time::GetDeltaTime() const
{
	return m_DeltaTime;
}
