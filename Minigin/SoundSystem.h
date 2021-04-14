#pragma once
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	
	virtual void PlaySound(const std::string& soundName, int volume) = 0;
	virtual void PlayMusic(const std::string& soundName, int volume) = 0;

	virtual void Mute() = 0;
	virtual void Unmute() = 0;
};

