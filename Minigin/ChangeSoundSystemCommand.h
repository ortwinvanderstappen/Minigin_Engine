#pragma once
#include "Command.h"
class ChangeSoundSystemCommand final : public Command
{
public:
	enum class SystemType
	{
		Basic = 0,
		Logging = 1,
		End = 2
	};
	ChangeSoundSystemCommand();
	bool Execute() override;

private:
	SystemType m_CurrentSystem = SystemType::Basic;
};

