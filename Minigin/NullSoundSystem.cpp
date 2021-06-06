#include "MiniginPCH.h"
#include "NullSoundSystem.h"

void NullSoundSystem::PlaySound(const std::string&)
{
}

void NullSoundSystem::Mute()
{
}

void NullSoundSystem::Unmute()
{
}

int NullSoundSystem::GetVolume() const
{
	return 0;
}

void NullSoundSystem::SetVolume(int)
{
}
