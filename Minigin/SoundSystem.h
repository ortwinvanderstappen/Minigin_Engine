#pragma once
class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	//SoundSystem(const SoundSystem& other) = delete;
	//SoundSystem(SoundSystem&& other) = delete;
	//SoundSystem& operator=(const SoundSystem& other) = delete;
	//SoundSystem& operator=(SoundSystem&& other) = delete;

	virtual void ProcessQueue() = 0;
	virtual void PlaySound(const std::string& soundName, int volume) = 0;
	virtual void PlayMusic(const std::string& soundName, int volume) = 0;
	
	virtual void Mute() = 0;
	virtual void Unmute() = 0;
	virtual void Stop() = 0;
};

