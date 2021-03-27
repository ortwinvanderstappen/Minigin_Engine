#pragma once
#include "SoundSystem.h"
class NullSoundSystem final : public SoundSystem
{
public:
	void ProcessQueue() override;
	void PlaySound(const std::string& soundName, int volume) override;
	void PlayMusic(const std::string& soundName, int volume) override;

	void Mute() override;
	void Unmute() override;
	void Stop() override;
};

