#include "stdafx.h"
#include "TileMovementComponent.h"

#include <GameObject.h>
#include <GameTime.h>
#include <Renderer.h>
#include <SDL_render.h>

#include "ArenaTile.h"
#include "GameArena.h"

TileMovementComponent::TileMovementComponent(ArenaTile* pStartTile, float movementspeed, bool canTriggerTile) :
	m_pTile(pStartTile),
	m_BaseMoveSpeed(movementspeed),
	m_CanTriggerTile(canTriggerTile),
	m_MoveState(MoveState::Idle),
	m_MovementProgress(0.f),
	m_MoveSpeed(0.f),
	m_SlowedMoveSpeed(3.f),
	m_BezierMultiplier(1.f),
	m_pGoalTile(nullptr)
{}

void TileMovementComponent::Initialize()
{
	m_MoveSpeed = m_BaseMoveSpeed;

	SpawnOnTile(m_pTile);

	// Setup allowed movements map (allow all movements by default)
	for (int i = 0; i < 4; ++i)
	{
		m_AllowedMovementsMap.insert(std::make_pair(static_cast<TileMovementComponent::MovementType>(i), true));
	}
}

void TileMovementComponent::Update()
{
	if (m_MoveState == MoveState::Moving)
	{
		const float deltaTime = Time::GetInstance().GetDeltaTime();

		//const Point2f& currentPosition = m_pParentObject->GetPosition();
		const Point2f& startPosition = m_StartPosition;
		const Point2f& goalPosition = m_pGoalTile->GetCenter();

		// Calculate quadratic bezier curve https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Quadratic_B%C3%A9zier_curves
		const float t = 1 - m_MovementProgress;
		const Point2f pointOnCurve = (startPosition * t + m_BezierPoint * m_MovementProgress) * t + (m_BezierPoint * t + goalPosition * m_MovementProgress) * m_MovementProgress;
		m_pParentObject->SetPosition(pointOnCurve);

		if (m_MovementProgress >= 1.f)
		{
			CompleteMovement();
		}
		m_MovementProgress += deltaTime * (1.f / m_MoveSpeed);
	}
}

bool TileMovementComponent::Move(MovementType movement)
{
	if (!m_pTile) return false;

	// Don't move if we're mid animation
	if (m_MoveState != MoveState::Idle) return false;

	// Don't allow disabled movements
	if (m_AllowedMovementsMap[movement] == false) return false;

	GameArena* pArena = m_pTile->GetArena();
	ArenaTile* pNewTile = pArena->GetNeighbourTile(m_pTile, movement);

	if (pNewTile)
	{
		for (CommandCallback& moveCallback : m_MoveCallbacks)
		{
			moveCallback();
		}

		MoveToTile(pNewTile);
		return true;
	}

	return false;
}

const std::unordered_map<TileMovementComponent::MovementType, bool>& TileMovementComponent::GetAllowedMovements() const
{
	return m_AllowedMovementsMap;
}

void TileMovementComponent::SetMovementAllowed(TileMovementComponent::MovementType movement, bool state)
{
	m_AllowedMovementsMap[movement] = state;
}

void TileMovementComponent::SetTile(ArenaTile* pTile)
{
	m_pTile = pTile;
	SetParentPosition();
}

void TileMovementComponent::MoveToTile(ArenaTile* pTile, bool isSlowed, float bezierMultiplier)
{
	const Point2f& currentPosition = m_pParentObject->GetPosition();
	const Point2f& goalPosition = pTile->GetCenter();

	// Set multipliers
	m_BezierMultiplier = bezierMultiplier;
	m_MoveSpeed = isSlowed ? m_SlowedMoveSpeed : m_BaseMoveSpeed;

	if (goalPosition.y < currentPosition.y)
		m_BezierPoint = Point2f(currentPosition.x, goalPosition.y * m_BezierMultiplier);
	else
		m_BezierPoint = Point2f(goalPosition.x, currentPosition.y * m_BezierMultiplier);

	m_StartPosition = m_pTile->GetCenter();
	m_pGoalTile = pTile;
	m_MoveState = MoveState::Moving;
	m_MovementProgress = 0.f;
}

ArenaTile* TileMovementComponent::GetTile() const
{
	return m_pTile;
}

void TileMovementComponent::SpawnOnTile(ArenaTile* pTile)
{
	m_pTile = pTile;
	m_MovementProgress = 0.f;

	// Start first movement animation (come in arena animation)
	SDL_Renderer* pRenderer = minigen::Renderer::GetInstance().GetSDLRenderer();
	// Obtain window size
	int width; int height; SDL_GetRendererOutputSize(pRenderer, &width, &height);

	// Calculate current direction from screen center
	const Point2f screenCenter{ static_cast<float>(width) * .5f, static_cast<float>(height) * .5f };
	Vector2f direction = Vector2f{ m_pTile->GetCenter() } - Vector2f{ screenCenter };
	const float length = direction.Normalize();

	// Set new position
	GetParent()->SetPosition(Point2f{ screenCenter + Point2f{direction.x, direction.y }*(length + 100.f) });
	m_MoveState = MoveState::Moving;
	m_StartPosition = GetParent()->GetPosition();
	m_pGoalTile = m_pTile;

	const Point2f& currentPosition = m_pParentObject->GetPosition();
	const Point2f& goalPosition = m_pGoalTile->GetCenter();

	if (goalPosition.y < currentPosition.y)
		m_BezierPoint = Point2f(currentPosition.x, goalPosition.y * m_BezierMultiplier);
	else
		m_BezierPoint = Point2f(goalPosition.x, currentPosition.y * m_BezierMultiplier);
}

TileMovementComponent::MoveState TileMovementComponent::GetMoveState() const
{
	return m_MoveState;
}

void TileMovementComponent::CompleteMovement()
{
	m_MoveState = MoveState::Idle;
	m_pTile = m_pGoalTile;
	SetParentPosition();
	TileMoved();
}

void TileMovementComponent::SetParentPosition() const
{
	if (m_pTile)
	{
		const Point2f& tileCenter = m_pTile->GetCenter();
		m_pParentObject->SetPosition(tileCenter.x, tileCenter.y);
	}
}

void TileMovementComponent::SubscribeToMoveCompleted(const CommandCallback& movedCallback)
{
	m_MovedCallbacks.push_back(movedCallback);
}

void TileMovementComponent::SubscribeToMove(const CommandCallback& moveCallback)
{
	m_MoveCallbacks.push_back(moveCallback);
}

void TileMovementComponent::TileMoved()
{
	// Don't trigger tiles on the first movement
	if (m_CanTriggerTile)
	{
		for (CommandCallback& movedCallback : m_MovedCallbacks)
		{
			movedCallback();
		}
	}
	else
	{
		m_CanTriggerTile = true;
	}
}
