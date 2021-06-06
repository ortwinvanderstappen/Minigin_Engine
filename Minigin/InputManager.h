#pragma once
#include <queue>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <XInput.h>
#include <Windows.h>

#include "Command.h"
#include "Singleton.h"
namespace minigen
{
	class Subject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();

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

		enum class HardwareType
		{
			controller,
			keyboard
		};

		enum class InputType
		{
			onKeyDown,
			onKeyUp,
			onKeyChange,
			continuous
		};

		enum class KeyState
		{
			pressed,
			released,
		};

		struct KeyInput
		{
			int id{INT_MAX};
			HardwareType hardwareType;
			InputType inputType;
			std::shared_ptr<Command> spInputCommand = nullptr;
			union InputButton
			{
				ControllerButton controllerButton;
				SDL_KeyCode keyboardButton;
			};
			InputButton inputButton;
			KeyState lastKeyState = KeyState::released;
		};

		bool HandleInputStates(std::vector<minigen::InputManager::KeyInput>& inputs);
		bool ProcessInput();
		void AddGlobalInput(const KeyInput& keyInput);

		bool IsInputTriggered(int inputId) const;

		const std::shared_ptr<Subject>& GetMouseSubject() const;
	
	private:
		bool IsControllerPressed(ControllerButton button) const;
		bool IsKeyboardButtonPressed(SDL_KeyCode keyCode) const;

		// State of the controller
		XINPUT_STATE m_State;
		// State of the keyboard
		std::vector<SDL_Event> m_KeyboardEvents{};
		
		// Remember the input type and the state that the input is in
		std::vector<KeyInput> m_GlobalInputs;
		// Queue of all commands that should run
		std::queue<KeyInput> m_InputQueue;
		// All the inputs that are not automatically handled by a command
		std::vector<KeyInput> m_CommandlessInputs{};

		std::shared_ptr<Subject> m_spMouseSubject;
	};
}
