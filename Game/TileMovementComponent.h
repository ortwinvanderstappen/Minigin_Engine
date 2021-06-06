#pragma once
#include "stdafx.h"

#include <Component.h>
#include <functional>
#include <structs.h>
#include <unordered_map>

class GameArena;
class ArenaTile;

class TileMovementComponent : public minigen::Component
{
public:
	typedef std::function<void()> CommandCallback;

	// Make sure down is 0 and right is 1!
	enum class MovementType
	{
		downLeft = 0,
		downRight = 1,
		upLeft,
		upRight,
		left,
		right
	};
	
	enum class MoveState
	{
		Idle,
		Moving
	};

	TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, float movementspeed);

	void Initialize() override;
	void Update() override;
	bool Move(MovementType movement);

	const std::unordered_map<MovementType, bool>& GetAllowedMovements() const;
	void SetMovementAllowed(TileMovementComponent::MovementType movement, bool state = true);

	void SetTile(ArenaTile* pTile);
	void MoveToTile(ArenaTile* pTile, bool isSlowed = false, float bezierMultiplier = 1.f);
	ArenaTile* GetTile() const;

	void SpawnOnTile(ArenaTile* pTile);

	MoveState GetMoveState() const;

	void CompleteMovement();
	void SetParentPosition() const;
	void SubscribeToMoveCompleted(const CommandCallback& movedCallback);
	void SubscribeToMove(const CommandCallback& moveCallback);

private:

	void TileMoved();

	GameArena* m_pArena;
	ArenaTile* m_pTile;
	MoveState m_MoveState;
	float m_MovementProgress;
	std::unordered_map<MovementType, bool> m_AllowedMovementsMap;

	ArenaTile* m_pGoalTile;
	Point2f m_StartPosition;
	float m_MoveSpeed;
	float m_BaseMoveSpeed;
	float m_SlowedMoveSpeed;
	float m_BezierMultiplier;
	Point2f m_BezierPoint;

	bool m_CanTriggerTile;

	std::vector<CommandCallback> m_MovedCallbacks;
	std::vector<CommandCallback> m_MoveCallbacks;
};

