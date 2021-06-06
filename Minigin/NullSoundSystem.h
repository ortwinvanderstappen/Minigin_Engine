#pragma once
#include "SoundSystem.h"
class NullSoundSystem final : public SoundSystem
{
public:
	void PlaySound(const std::string& soundName) override;

	void Mute() override;
	void Unmute() override;

	int GetVolume() const override;
	void SetVolume(int volume) override;
};

