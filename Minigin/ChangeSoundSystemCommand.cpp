#include "MiniginPCH.h"
#include "ChangeSoundSystemCommand.h"


#include "BasicSoundSystem.h"
#include "LoggingSoundSystem.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

ChangeSoundSystemCommand::ChangeSoundSystemCommand()
{}

bool ChangeSoundSystemCommand::Execute()
{
	int currentSystem = static_cast<int>(m_CurrentSystem);

	// Increment system
	++currentSystem;
	if (currentSystem == static_cast<int>(SystemType::End))
	{
		currentSystem = 0;
	}
	m_CurrentSystem = static_cast<SystemType>(currentSystem);

	std::shared_ptr<SoundSystem> spBasicSoundSystem = std::make_shared<BasicSoundSystem>();

	std::cout << "Swapping sound system\n";
	switch (static_cast<SystemType>(currentSystem))
	{
	case SystemType::Basic:
	{
		ServiceLocator::RegisterSoundSystem(spBasicSoundSystem);
	}
	break;
	case SystemType::Logging:
	{
		std::shared_ptr<SoundSystem> spLoggingSoundSystem = std::make_shared<LoggingSoundSystem>(spBasicSoundSystem);
		ServiceLocator::RegisterSoundSystem(spLoggingSoundSystem);
	}
	break;
	case SystemType::End:
		std::cout << "ERROR: ChangeSoundSystemCommand: No sound system found, end\n";
		break;
	default:
		std::cout << "ERROR: ChangeSoundSystemCommand: No sound system found, default\n";
	}

	return true;
}
