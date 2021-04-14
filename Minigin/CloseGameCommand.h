#pragma once
#include "Command.h"
class CloseGameCommand final: public Command
{
public:
	bool Execute() override;
};

