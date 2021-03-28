#pragma once
#include "SoundSystem.h"
class LoggingSoundSystem final : public SoundSystem
{
public:
	LoggingSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem);
	~LoggingSoundSystem();

	void ProcessQueue() override;
	void PlaySound(const std::string& soundName, int volume) override;
	void PlayMusic(const std::string& soundName, int volume) override;
	void Mute() override;
	void Unmute() override;

private:
	std::shared_ptr<SoundSystem> m_spSoundSystem = nullptr;
};

