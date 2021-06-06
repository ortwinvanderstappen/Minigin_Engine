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
	void MoveToTile(ArenaTile* pTile, bool isSlowed = false, float bezierMultiplier = 1.f);
	ArenaTile* GetTile() const;

	void SpawnOnTile(ArenaTile* pTile);

	void CompleteMovement();
	void SetParentPosition() const;
	void SubscribeToMoveCompleted(const CommandCallback& movedCallback);
	void SubscribeToMove(const CommandCallback& moveCallback);

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
	Point2f m_StartPosition;
	float m_BezierMultiplier;
	Point2f m_BezierPoint;

	std::vector<CommandCallback> m_MovedCallbacks;
	std::vector<CommandCallback> m_MoveCallbacks;

	float m_MoveSpeedMultiplier;
	float m_BaseMoveSpeedMultiplier;
	float m_SlowedMoveSpeedMultiplier;
};

