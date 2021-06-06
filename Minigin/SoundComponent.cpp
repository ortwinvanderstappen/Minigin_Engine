#include "MiniginPCH.h"
#include "SoundComponent.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

minigen::SoundComponent::SoundComponent(const std::string& soundPath) :
	m_SoundPath(soundPath)
{}

void minigen::SoundComponent::PlaySoundEffect() const
{
	std::shared_ptr<SoundSystem> spSoundSystem = ServiceLocator::GetSoundSystem();
	spSoundSystem->PlaySound(m_SoundPath);
}