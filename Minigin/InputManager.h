#pragma once
#include <queue>
#include <unordered_map>
#include <XInput.h>

#include "CommandManager.h"
#include "Singleton.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonUp,
		ButtonDown,
		ButtonLeft,
		ButtonRight,
		StartButton,
		BackButton,
		LeftStickDown,
		RightStickDown,
		LeftTrigger,
		RightTrigger,
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		
		enum class InputType
		{
			onKeyDown,
			onKeyUp,
			onKeyChange,
			continuous
		};

		bool ProcessInput();
		void AddInput(ControllerButton button, InputType inputType = InputType::continuous);
		void BindInput(ControllerButton button, CommandManager::CommandType commandType);

	private:
		enum class KeyState
		{
			pressed,
			released,
		};
		bool IsPressed(ControllerButton button) const;
		bool ProcessKeyboardInput();
		bool ProcessGamepadInput();

		std::shared_ptr<CommandManager> m_spCommandManager;
		// State of the controller
		XINPUT_STATE m_State;
		
		// Remember the input type and the state that the input is in
		std::unordered_map<ControllerButton, std::pair<InputType, KeyState>> m_InputMap;
		// Queue of all commands that should run
		std::queue<ControllerButton> m_InputQueue;
		// Map each button to a command
		std::unordered_map<ControllerButton, std::shared_ptr<Command>> m_spCommandsMap;
	};

}
