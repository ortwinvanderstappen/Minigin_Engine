#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Subject.h"

minigen::InputManager::InputManager() :
	m_State{},
	m_GlobalInputs{},
	m_InputQueue{},
	m_spMouseSubject(std::make_shared<Subject>())
{
}

bool minigen::InputManager::ProcessInput()
{
	// Get all keyboard events for this frame
	m_KeyboardEvents.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}

		if (e.type == SDL_KEYDOWN)
		{
			m_KeyboardEvents.push_back(e);
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			m_spMouseSubject->Notify(nullptr, Observer::Event::mouse_click);
		}
	}

	// Check if any global inputs have been triggered (inputs shared across all scenes, always active)
	const bool success = HandleInputStates(m_GlobalInputs);
	if (!success) return false;

	// Clear the commandless inputs
	m_CommandlessInputs.clear();

	// Handle all active inputs, process the queue
	while (!m_InputQueue.empty())
	{
		KeyInput keyInput = m_InputQueue.front();
		if (keyInput.spInputCommand != nullptr)
		{
			if (!keyInput.spInputCommand->Execute())
				return false;
		}
		else
		{
			m_CommandlessInputs.push_back(keyInput);
		}

		// Remove handled input from the queue
		m_InputQueue.pop();
	}

	return success;
}

void minigen::InputManager::AddGlobalInput(const KeyInput& keyInput)
{
	m_GlobalInputs.push_back(keyInput);
}

bool minigen::InputManager::IsInputTriggered(int inputId) const
{
	// Try to find the desired input and see if it's triggered
	for (const KeyInput& input : m_CommandlessInputs)
	{
		if (input.id == inputId)
		{
			return true;
		};
	}

	return false;
}

const std::shared_ptr<minigen::Subject>& minigen::InputManager::GetMouseSubject() const
{
	return m_spMouseSubject;
}

bool minigen::InputManager::IsControllerPressed(ControllerButton button) const
{
	return m_State.Gamepad.wButtons & static_cast<int>(button);
}

bool minigen::InputManager::IsKeyboardButtonPressed(SDL_KeyCode keyCode) const
{
	for (const SDL_Event& e : m_KeyboardEvents)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == keyCode)
			{
				return true;
			}
		}
	}

	return false;
}

bool minigen::InputManager::HandleInputStates(std::vector<KeyInput>& inputs)
{
	DWORD dwResult;
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	dwResult = XInputGetState(0, &m_State);

	// Check which inputs are fulfilled
	for (KeyInput& input : inputs)
	{
		const HardwareType hardwareType = input.hardwareType;
		const InputType inputType = input.inputType;

		KeyState currentKeyState = KeyState::released;

		// Check if the key was pressed
		switch (hardwareType)
		{
		case HardwareType::controller:
		{
			// Check if the controller is connected
			if (dwResult == ERROR_SUCCESS)
			{
				if (IsControllerPressed(input.inputButton.controllerButton))
					currentKeyState = KeyState::pressed;
			}
			break;
		}
		case HardwareType::keyboard:
		{
			if (IsKeyboardButtonPressed(input.inputButton.keyboardButton))
				currentKeyState = KeyState::pressed;
			break;
		}
		default:;
		}

		// Key was pressed
		if (currentKeyState == KeyState::pressed)
		{
			// KeyDown
			if (inputType == InputType::onKeyDown)
			{
				// Check if keystate changed
				if (input.lastKeyState != currentKeyState)
				{
					m_InputQueue.push(input);
				}
			}
			// KeyUp
			else if (inputType == InputType::continuous)
			{
				m_InputQueue.push(input);
			}
		}
		// Key was released
		else
		{
			currentKeyState = KeyState::released;

			// KeyUp
			if (inputType == InputType::onKeyUp)
			{
				if (input.lastKeyState != currentKeyState)
				{
					m_InputQueue.push(input);
				}
			}
		}

		// Key was changed
		if (inputType == InputType::onKeyChange)
		{
			// Check if key changed
			if (input.lastKeyState != currentKeyState)
			{
				m_InputQueue.push(input);
			}
		}

		// Set key state
		input.lastKeyState = currentKeyState;
	}
	return true;
}
