#pragma once
#include "Command.h"
class OpenGameSceneCommand final: public Command
{
public:
	bool Execute() override;
};

