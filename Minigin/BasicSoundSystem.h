#pragma once
#include <queue>
#include <mutex>

#include "SoundSystem.h"
class BasicSoundSystem final : public SoundSystem
{
public:
	BasicSoundSystem();
	~BasicSoundSystem();

	void ProcessQueue() override;
	void PlaySound(const std::string& soundName, int volume) override;
	void PlayMusic(const std::string& soundName, int volume) override;

	void Mute() override;
	void Unmute() override;
private:
	std::thread m_SoundThread;
	
	std::queue<std::pair<std::string, int>> m_SoundQueue;

	int m_MaxVolume = 100;
	bool m_IsRunning = true;
	bool m_IsMuted = false;

	std::condition_variable m_PlayCondition;
	std::mutex m_Mutex;
};

