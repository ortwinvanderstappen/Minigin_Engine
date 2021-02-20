#include "MiniginPCH.h"
#include "Time.h"

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
