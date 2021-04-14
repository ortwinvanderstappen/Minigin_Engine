#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

minigen::InputManager::InputManager() :
	m_spCommandManager(std::make_shared<CommandManager>()),
	m_State{},
	m_InputMap{},
	m_InputQueue{},
	m_spCommandsMap{}
{
}

bool minigen::InputManager::ProcessInput()
{
	bool success = ProcessKeyboardInput();
	if (!success) return false;

	success = ProcessGamepadInput();
	if (!success) return false;

	// Handle all active inputs
	while (!m_InputQueue.empty())
	{
		ControllerButton controllerButton = m_InputQueue.front();
		if (m_spCommandsMap.find(controllerButton) != m_spCommandsMap.end())
		{
			m_spCommandsMap.at(controllerButton)->Execute();
		}

		m_InputQueue.pop();
	}

	return true;
}

void minigen::InputManager::AddInput(ControllerButton button, InputType inputType)
{
	// Check if input already exists
	if (m_InputMap.find(button) == m_InputMap.end())
	{
		// Create a new input
		m_InputMap.insert(std::make_pair(button, std::make_pair(inputType, KeyState::pressed)));
	}
	else
	{
		// Change input
		m_InputMap.at(button).first = inputType;
	}
}

void minigen::InputManager::BindInput(ControllerButton button, CommandManager::CommandType commandType)
{
	std::shared_ptr<Command> spCommand = m_spCommandManager->GetCommand(commandType);
	BindInput(button, spCommand);
}

void minigen::InputManager::BindInput(ControllerButton button, std::shared_ptr<Command> spCommand)
{
	// Check if input exists
	if (m_InputMap.find(button) == m_InputMap.end())
	{
		// Input does not exist, create new input first
		AddInput(button);
	}

	// Check if input already has a command
	if (m_spCommandsMap.find(button) != m_spCommandsMap.end())
	{
		// Change input command
		m_spCommandsMap.at(button) = spCommand;
	}
	else
	{
		// Create a new input command entry
		m_spCommandsMap.insert(std::make_pair(button, spCommand));
	}
}

bool minigen::InputManager::IsPressed(ControllerButton button) const
{
	return m_State.Gamepad.wButtons & static_cast<int>(button);
}

bool minigen::InputManager::ProcessKeyboardInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{

		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
	}

	return true;
}

bool minigen::InputManager::ProcessGamepadInput()
{
	DWORD dwResult;
	ZeroMemory(&m_State, sizeof(XINPUT_STATE));
	dwResult = XInputGetState(0, &m_State);
	// Check if the controller is connected
	if (dwResult == ERROR_SUCCESS)
	{
		// Check which inputs are fulfilled
		std::for_each(m_InputMap.begin(), m_InputMap.end(),
			[this](std::pair<ControllerButton, std::pair<InputType, KeyState>> pair)
			{
				const KeyState lastKeyState = pair.second.second;
				KeyState currentKeyState;

				const ControllerButton controllerButton = pair.first;
				const InputType inputType = pair.second.first;
				const KeyState keyState = pair.second.second;

				// Check if key is pressed
				if (IsPressed(controllerButton))
				{
					currentKeyState = KeyState::pressed;

					// KeyDown
					if (inputType == InputType::onKeyDown)
					{
						// Check if keystate changed
						if (lastKeyState != currentKeyState)
						{
							m_InputQueue.push(controllerButton);
						}
					}
					// KeyUp
					else if (inputType == InputType::continuous)
					{
						m_InputQueue.push(controllerButton);
					}
				}
				// Key is released
				else
				{
					currentKeyState = KeyState::released;

					// KeyUp
					if (inputType == InputType::onKeyUp)
					{
						if (lastKeyState != currentKeyState)
						{
							m_InputQueue.push(controllerButton);
						}
					}
				}

				if (inputType == InputType::onKeyChange)
				{
					// Check if key changed
					if (lastKeyState != currentKeyState)
					{
						m_InputQueue.push(controllerButton);
					}
				}

				// Set key state
				m_InputMap.at(controllerButton).second = currentKeyState;
			});
	}
	else
	{
		// TODO: show in gui
		std::cout << "Failed to find controller\n";
	}

	return true;
}
