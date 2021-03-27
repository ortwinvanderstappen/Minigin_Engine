#pragma once

class NullSoundSystem;
class SoundSystem;

class ServiceLocator final
{
	static std::shared_ptr<SoundSystem> m_spCurrentSoundSystem;
public:
	static std::shared_ptr<SoundSystem> GetSoundSystem();
	static void RegisterSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem);
private:
	static std::shared_ptr<NullSoundSystem> m_spNullSoundSystem;
};

