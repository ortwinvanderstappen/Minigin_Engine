#include "MiniginPCH.h"
#include "LoggingSoundSystem.h"

LoggingSoundSystem::LoggingSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem) :
	m_spSoundSystem{ spSoundSystem }
{}

LoggingSoundSystem::~LoggingSoundSystem()
{
	std::cout << "Stopped LoggingSoundSystem\n";
}

void LoggingSoundSystem::PlaySound(const std::string& soundName, int volume)
{
	std::cout << "Playing sound " << soundName << " with volume " << volume << "\n";
	m_spSoundSystem->PlaySound(soundName, volume);
}

void LoggingSoundSystem::PlayMusic(const std::string& soundName, int volume)
{
	std::cout << "Playing music " << soundName << " with volume " << volume << "\n";
	m_spSoundSystem->PlayMusic(soundName, volume);
}

void LoggingSoundSystem::Mute()
{
	std::cout << "Muted soundsystem\n";
	m_spSoundSystem->Mute();
}

void LoggingSoundSystem::Unmute()
{
	std::cout << "Unmuted soundsystem\n";
	m_spSoundSystem->Unmute();
}
