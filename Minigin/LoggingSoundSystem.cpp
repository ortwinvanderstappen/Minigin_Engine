#include "MiniginPCH.h"
#include "LoggingSoundSystem.h"

LoggingSoundSystem::LoggingSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem) :
	m_spSoundSystem{ spSoundSystem }
{}

LoggingSoundSystem::~LoggingSoundSystem()
{
	std::cout << "Stopped LoggingSoundSystem\n";
}

void LoggingSoundSystem::PlaySound(const std::string& soundName)
{
	std::cout << "Playing sound " << soundName << "\n";
	m_spSoundSystem->PlaySound(soundName);
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

int LoggingSoundSystem::GetVolume() const
{
	std::cout << "Fetching sound volume\n";
	return m_spSoundSystem->GetVolume();
}

void LoggingSoundSystem::SetVolume(int volume)
{
	std::cout << "Setting volume to " << volume << "\n";
	m_spSoundSystem->SetVolume(volume);
}
