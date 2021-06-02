#pragma once
#include "Command.h"
#include <functional>

class CustomCommand : public Command
{
public:
	typedef std::function<void ()> CommandCallback;

	CustomCommand(CommandCallback callback);
	bool Execute() override;

private:
	CommandCallback m_Callback;
};

