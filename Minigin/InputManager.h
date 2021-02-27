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
		ButtonUp = 0x0001,
		ButtonDown = 0x0002,
		ButtonLeft = 0x0004,
		ButtonRight = 0x0008,
		StartButton = 0x0010,
		BackButton = 0x0020,
		LeftStickDown = 0x0040,
		RightStickDown = 0x0080,
		LeftTrigger = 0x0100,
		RightTrigger = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
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
		void BindInput(ControllerButton button, std::shared_ptr<Command> spCommand);

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
