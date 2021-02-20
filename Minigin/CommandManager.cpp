#include "MiniginPCH.h"
#include "CommandManager.h"

#include "TestCommand.h"

CommandManager::CommandManager()
{
	InitializeCommands();
}

std::shared_ptr<Command> CommandManager::GetCommand(CommandType commandType)
{
	if (m_spCommandsMap.find(commandType) != m_spCommandsMap.end())
	{
		return m_spCommandsMap.at(commandType);
	}

	return nullptr;
}

void CommandManager::InitializeCommands()
{
	AddCommand(CommandType::test);
}

void CommandManager::AddCommand(CommandType commandType)
{
	std::shared_ptr<Command> spCommand;
	switch (commandType)
	{
	case CommandType::test:
		spCommand = std::make_shared<TestCommand>();
		break;
	default:
		spCommand = nullptr;
	}

	if (spCommand)
		m_spCommandsMap.insert(std::make_pair(commandType, spCommand));
}
