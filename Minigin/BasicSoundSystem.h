#pragma once
#include <queue>
#include <mutex>

#include "SoundSystem.h"
class BasicSoundSystem final : public SoundSystem
{
public:
	void ProcessQueue() override;
	void PlaySound(const std::string& soundName, int volume) override;
	void PlayMusic(const std::string& soundName, int volume) override;

	void Mute() override;
	void Unmute() override;
	
	void Stop() override;
private:
	std::queue<std::pair<std::string, int>> m_SoundQueue;

	int m_MaxVolume = 100;
	bool m_IsRunning = true;
	bool m_IsMuted = false;

	std::condition_variable m_PlayCondition;
	std::mutex m_Mutex;
};

