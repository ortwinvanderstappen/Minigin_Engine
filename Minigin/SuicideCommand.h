#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;
	class SuicideCommand final : public Command
	{
	public:
		SuicideCommand(std::shared_ptr<dae::GameObject> gameObject);
		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_ObjectToKill = nullptr;
	};
}

