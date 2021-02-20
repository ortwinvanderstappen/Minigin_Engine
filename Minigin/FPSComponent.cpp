#include "MiniginPCH.h"
#include "FPSComponent.h"

#include <algorithm>
#include <numeric>

#include "Time.h"

FPSComponent::FPSComponent(const Point2f& position)
{
	AddText(0, "FPS: " + std::to_string(m_CurrentFPS), position, 20);

	m_FpsHistory = std::vector<int>(m_FrameHistoryCount);
}

void FPSComponent::Update()
{
	// Add delta time to the total time
	const float& deltaTime = Time::GetInstance().DeltaTime();
	m_TimePassed += deltaTime;
	// Add fps to history
	m_FpsHistory[m_Framecount] = static_cast<int>(1.f / deltaTime);
	// Increase the current frame count
	m_Framecount = (m_Framecount + 1) % m_FrameHistoryCount;
	// Check if 1 second has passed
	if (m_TimePassed >= 1.f)
	{
		// Calculate average fps
		const int sum = std::accumulate(m_FpsHistory.begin(), m_FpsHistory.end(), 0);
		m_CurrentFPS = static_cast<int>(static_cast<float>(sum) / static_cast<float>(m_FrameHistoryCount));

		// Set text
		SetText(0, "FPS: " + std::to_string(m_CurrentFPS));

		// Subtract 1 second from time
		m_TimePassed = 0.f;
	}

	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [](std::pair<int, std::shared_ptr<dae::TextObject>> textPair)
		{
			textPair.second->Update();
		}
	);
}

const int FPSComponent::GetFPS() const
{
	return m_CurrentFPS;
}
