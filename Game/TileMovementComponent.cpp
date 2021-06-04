#include "TileMovementComponent.h"

#include <iostream>


#include "ArenaTile.h"
#include "GameArena.h"
#include "GameObject.h"
#include "GameTime.h"

TileMovementComponent::TileMovementComponent(GameArena* pArena, ArenaTile* pStartTile, float movementCooldown) :
	m_pArena(pArena),
	m_pTile(pStartTile),
	m_MovementCooldown(movementCooldown),
	m_MovementTimer(0.f),
	m_MovedCallbacks()
{}

void TileMovementComponent::Initialize()
{
	SetParentPosition();
}

void TileMovementComponent::Update()
{
	if (m_MovementTimer < m_MovementCooldown)
	{
		m_MovementTimer += Time::GetInstance().GetDeltaTime();
	}
}

bool TileMovementComponent::Move(MovementType movement)
{
	if (!m_pTile) return false;

	// Don't accept input when movement is on cooldown
	if (m_MovementTimer < m_MovementCooldown)
		return false;

	// Apply movement cooldown
	m_MovementTimer -= m_MovementCooldown;

	GameArena* pArena = m_pTile->GetArena();
	ArenaTile* pNewTile = pArena->GetNeighbourTile(m_pTile, movement);

	if (pNewTile)
	{
		m_pTile = pNewTile;
		SetParentPosition();
		TileMoved();
		return true;
	}

	return false;
}

void TileMovementComponent::SetTile(ArenaTile* pTile)
{
	m_pTile = pTile;
	SetParentPosition();
}

ArenaTile* TileMovementComponent::GetTile() const
{
	return m_pTile;
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
	std::cout << "Moved to tile with index: " << m_pTile->GetIndex() << "\n";
	
	for(CommandCallback& movedCallback: m_MovedCallbacks)
	{
		movedCallback();
	}
}
