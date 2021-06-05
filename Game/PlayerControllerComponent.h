#pragma once
#include <Component.h>

namespace minigen {
	class InputComponent;
}

class TileMovementComponent;

class PlayerControllerComponent : public minigen::Component
{
public:
	
	enum class HardwareType
	{
		Keyboard,
		Controller,
		Both
	};
	
	PlayerControllerComponent(HardwareType hardwareType);

	void Initialize() override;
	void Update() override;

private:
	enum class InputId
	{
		up,
		right,
		down,
		left
	};

	static void CreateKeyboardInputs(const std::shared_ptr<minigen::InputComponent>& spInputComponent);
	static void CreateControllerInputs(const std::shared_ptr<minigen::InputComponent>& spInputComponent);

	void CheckKeyboardInputs() const;
	void CheckControllerInputs() const;
	
	HardwareType m_HardwareType;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
};

