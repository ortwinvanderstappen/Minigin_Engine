#pragma once
#include <Component.h>
class TileMovementComponent;

class PlayerControllerComponent : public minigen::Component
{
public:
	
	enum class HardwareType
	{
		Keyboard,
		Controller
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

	void CreateKeyboardInputs() const;
	void CreateControllerInputs() const;
	
	HardwareType m_HardwareType;
	std::shared_ptr<TileMovementComponent> m_spTileMovementComponent;
};

