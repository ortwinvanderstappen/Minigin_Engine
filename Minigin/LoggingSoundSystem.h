#pragma once
#include "SoundSystem.h"
class LoggingSoundSystem final : public SoundSystem
{
public:
	LoggingSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem);
	~LoggingSoundSystem();

	void PlaySound(const std::string& soundName) override;
	void Mute() override;
	void Unmute() override;

	int GetVolume() const override;
	void SetVolume(int volume) override;
private:
	std::shared_ptr<SoundSystem> m_spSoundSystem = nullptr;
};

