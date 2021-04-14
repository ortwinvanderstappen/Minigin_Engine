#pragma once
#include "Command.h"

namespace minigen
{
	class GameObject;
	class SuicideCommand final : public Command
	{
	public:
		SuicideCommand(std::shared_ptr<minigen::GameObject> gameObject);
		bool Execute() override;

	private:
		std::shared_ptr<GameObject> m_ObjectToKill = nullptr;
	};
}

