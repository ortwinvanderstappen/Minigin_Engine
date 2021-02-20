#pragma once
#include "Command.h"
class TestCommand final: public Command
{
public:
	TestCommand() = default;
	void Execute() override;
};

