#pragma once
#include "Command.h"
class PlaySoundCommand final : public Command
{
public:
	PlaySoundCommand(const std::string soundPath);

	void Execute() override;
private:
	std::string m_Path;
};

