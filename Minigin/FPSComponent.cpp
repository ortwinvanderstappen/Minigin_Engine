#include "MiniginPCH.h"
#include "FPSComponent.h"

#include <algorithm>

#include "Time.h"

FPSComponent::FPSComponent(const Point2f& position)
{
	AddText(0, "FPS: " + std::to_string(m_CurrentFPS), position, 20);
}

void FPSComponent::Update()
{
	// Add delta time to the total time
	const float& deltaTime = Time::GetInstance().DeltaTime();
	m_TimePassed += deltaTime;
	// Increase the current frame count
	++m_Framecount;
	// Check if 1 second has passed
	if (m_TimePassed >= 1.f)
	{
		// Set fps
		m_CurrentFPS = static_cast<int>(static_cast<float>(m_Framecount) / m_TimePassed);

		// Set text
		SetText(0, "FPS: " + std::to_string(m_CurrentFPS));

		// Reset frame count
		m_Framecount = 0;
		// Subtract 1 second from time
		m_TimePassed = 0.f;
	}

	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [](std::pair<int, std::shared_ptr<dae::TextObject>> textPair)
		{
			textPair.second->Update();
		}
	);
}

const int& FPSComponent::GetFPS() const
{
	return m_CurrentFPS;
}
