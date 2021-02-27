#pragma once
#include <unordered_map>

#include "Command.h"

class CommandManager
{
public:
	CommandManager();

	enum class CommandType
	{
		suicide
	};
	
	std::shared_ptr<Command> GetCommand(CommandType commandType);

private:
	void InitializeCommands();
	void AddCommand(CommandType commandType);
	
	std::unordered_map<CommandType, std::shared_ptr<Command>> m_spCommandsMap{};
};
