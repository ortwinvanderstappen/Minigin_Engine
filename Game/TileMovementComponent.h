#pragma once
#include <Component.h>
#include <functional>
#include <unordered_map>
class GameArena;
class ArenaTile;

class TileMovementComponent : public minigen::Component
{
public:
	typedef std::function<void ()> CommandCallback;
	
	// Make sure down is 0 and right is 1!
	enum class MovementType
	{
		down = 0,
		right = 1,
		left,
		up
	};
	
	TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, bool allowHorizontalMovement = false, bool upIsUp = true);

	void Initialize() override;
	void Update() override;
	bool Move(MovementType movement);

	const std::unordered_map<MovementType, bool>& GetAllowedMovements() const;
	void SetMovementAllowed(TileMovementComponent::MovementType movement, bool state = true);

	void SetTile(ArenaTile* pTile);
	void MoveToTile(ArenaTile* pTile);
	ArenaTile* GetTile() const;

	void CompleteMovement();
	void SetParentPosition() const;
	void SubscribeToMoved(const CommandCallback& movedCallback);

private:
	enum class MoveState
	{
		Idle,
		Moving
	};
	
	void TileMoved();
	
	GameArena* m_pArena;
	ArenaTile* m_pTile;
	bool m_AllowHorizontalMovement;
	bool m_UpIsUp;
	MoveState m_MoveState;
	float m_MovementProgress;
	std::unordered_map<TileMovementComponent::MovementType, bool> m_AllowedMovementsMap;

	ArenaTile* m_pGoalTile;

	std::vector<CommandCallback> m_MovedCallbacks;

	float m_MoveSpeedMultiplier = 0.f;
	float m_BaseMoveSpeedMultiplier = 2.5f;
	float m_SlowedMoveSpeedMultiplier = .3f;
};

