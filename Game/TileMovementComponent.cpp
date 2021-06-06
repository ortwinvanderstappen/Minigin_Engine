#include "TileMovementComponent.h"

#include <iostream>


#include "ArenaTile.h"
#include "GameArena.h"
#include "GameObject.h"
#include "GameTime.h"
#include <cmath>
#include <SDL_render.h>

#include "Renderer.h"

TileMovementComponent::TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, bool allowHorizontalMovement, bool upIsUp) :
	m_pArena(pArena),
	m_pTile(pStartTile),
	m_AllowHorizontalMovement(allowHorizontalMovement),
	m_UpIsUp(upIsUp),
	m_MoveState(MoveState::Idle),
	m_MovementProgress(0.f),
	m_AllowedMovementsMap(),
	m_MovedCallbacks(),
	m_MoveSpeedMultiplier(0.f),
	m_BaseMoveSpeedMultiplier(2.5f),
	m_SlowedMoveSpeedMultiplier(.3f)
{}

void TileMovementComponent::Initialize()
{
	m_MoveSpeedMultiplier = m_BaseMoveSpeedMultiplier;

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

		const Point2f& currentPosition = m_pParentObject->GetPosition();
		const Point2f& startPosition = m_StartPosition;
		const Point2f& goalPosition = m_pGoalTile->GetCenter();

		// Calculate intermediate bezier point
		Point2f bezierPoint;

		if (goalPosition.y < currentPosition.y)
			bezierPoint = Point2f(currentPosition.x, goalPosition.y);
		else
			bezierPoint = Point2f(goalPosition.x, currentPosition.y);

		// Calculate quadratic bezier curve https://en.wikipedia.org/wiki/B%C3%A9zier_curve#Quadratic_B%C3%A9zier_curves
		const float t = 1 - m_MovementProgress;
		const Point2f pointOnCurve = (startPosition * t + bezierPoint * m_MovementProgress) * t + (bezierPoint * t + goalPosition * m_MovementProgress) * m_MovementProgress;
		m_pParentObject->SetPosition(pointOnCurve);

		if (m_MovementProgress >= 1.f)
		{
			CompleteMovement();
		}
		m_MovementProgress += deltaTime * m_MoveSpeedMultiplier;
	}
}

bool TileMovementComponent::Move(MovementType movement)
{
	if (!m_pTile) return false;

	// Don't move if we're mid animation
	if (m_MoveState != MoveState::Idle) return false;

	// Don't allow disabled movements
	if (m_AllowedMovementsMap[movement] == false) return false;

	m_MoveSpeedMultiplier = m_BaseMoveSpeedMultiplier;

	GameArena* pArena = m_pTile->GetArena();
	ArenaTile* pNewTile = pArena->GetNeighbourTile(m_pTile, movement, m_AllowHorizontalMovement, m_UpIsUp);

	if (pNewTile)
	{
		m_pGoalTile = pNewTile;
		m_StartPosition = m_pTile->GetCenter();
		m_MoveState = MoveState::Moving;
		m_MovementProgress = 0.f;
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

void TileMovementComponent::MoveToTile(ArenaTile* pTile)
{
	m_pGoalTile = pTile;
	m_MoveState = MoveState::Moving;
	m_MovementProgress = 0.f;
	m_MoveSpeedMultiplier = m_SlowedMoveSpeedMultiplier;
}

ArenaTile* TileMovementComponent::GetTile() const
{
	return m_pTile;
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

void TileMovementComponent::SubscribeToMoved(const CommandCallback& movedCallback)
{
	m_MovedCallbacks.push_back(movedCallback);
}

void TileMovementComponent::TileMoved()
{
	for (CommandCallback& movedCallback : m_MovedCallbacks)
	{
		movedCallback();
	}
}
