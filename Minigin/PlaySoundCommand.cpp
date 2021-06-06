#include "MiniginPCH.h"
#include "PlaySoundCommand.h"

#include "ServiceLocator.h"
#include "SoundSystem.h"

PlaySoundCommand::PlaySoundCommand(const std::string soundPath) :
	m_Path{soundPath}
{}

bool PlaySoundCommand::Execute()
{
	ServiceLocator::GetSoundSystem()->PlaySound(m_Path);
	return true;
}
