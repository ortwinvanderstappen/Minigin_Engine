#include "Ugg.h"


#include "GameObject.h"
#include "RandomAIComponent.h"
#include "TileMovementComponent.h"

Ugg::Ugg(GameArena* pArena, ArenaTile* pTile) :
	m_pArena(pArena),
	m_pTile(pTile),
	m_spTileMovementComponent(std::make_shared<TileMovementComponent>(pArena, pTile)),
	m_MovementDelay(1.f)
{}

void Ugg::Initialize()
{
	GetParent()->AddComponent(m_spTileMovementComponent);
	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::down, false);
	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::right, false);

	const std::shared_ptr<RandomAIComponent> spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena, 1.f, true, false);
	GetParent()->AddComponent(spRandomAIComponent);
}

void Ugg::Update()
{}
