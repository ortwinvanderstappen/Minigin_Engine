#include "MiniginPCH.h"
#include "ServiceLocator.h"

#include "NullSoundSystem.h"

std::shared_ptr<SoundSystem> ServiceLocator::m_spCurrentSoundSystem = nullptr;
std::shared_ptr<NullSoundSystem> ServiceLocator::m_spNullSoundSystem = std::make_shared<NullSoundSystem>();

std::shared_ptr<SoundSystem> ServiceLocator::GetSoundSystem()
{
	if(m_spCurrentSoundSystem == nullptr)
	{
		m_spCurrentSoundSystem = m_spNullSoundSystem;
	}
	
	return m_spCurrentSoundSystem;
}

void ServiceLocator::RegisterSoundSystem(std::shared_ptr<SoundSystem> spSoundSystem)
{
	if (spSoundSystem == nullptr)
	{
		m_spCurrentSoundSystem = m_spNullSoundSystem;
	}
	else
		m_spCurrentSoundSystem = spSoundSystem;
}
