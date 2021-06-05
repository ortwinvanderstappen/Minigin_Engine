#pragma once
#include <Component.h>
#include <functional>
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
	
	TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile);

	void Initialize() override;
	void Update() override;
	bool Move(MovementType movement);

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
	MoveState m_MoveState;
	float m_MovementProgress;

	ArenaTile* m_pGoalTile;

	std::vector<CommandCallback> m_MovedCallbacks;

	float m_MoveSpeedMultiplier = 0.f;
	float m_BaseMoveSpeedMultiplier = 2.5f;
	float m_SlowedMoveSpeedMultiplier = .3f;
};

