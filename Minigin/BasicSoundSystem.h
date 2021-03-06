#pragma once
#include <queue>
#include <mutex>

#include "SoundSystem.h"
class BasicSoundSystem final : public SoundSystem
{
public:
	BasicSoundSystem();
	~BasicSoundSystem();

	void PlaySound(const std::string& soundName) override;

	void Mute() override;
	void Unmute() override;

	int GetVolume() const override;
	void SetVolume(int volume) override;
private:
	void ProcessQueue();
	
	std::thread m_SoundThread;
	
	std::queue<std::pair<std::string, int>> m_SoundQueue;

	int m_MaxVolume = 100;
	int m_Volume;
	bool m_IsRunning = true;
	bool m_IsMuted = false;

	std::condition_variable m_PlayCondition;
	std::mutex m_Mutex;
};

