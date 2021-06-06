#pragma once
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	
	virtual void PlaySound(const std::string& soundName) = 0;

	virtual void Mute() = 0;
	virtual void Unmute() = 0;

	virtual int GetVolume() const = 0;
	virtual void SetVolume(int volume) = 0;
};

