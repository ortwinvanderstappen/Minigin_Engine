#include "TileRevertCreature.h"

#include <iostream>


#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameArena.h"
#include "ImageRenderComponent.h"
#include "RandomAIComponent.h"
#include "TileMovementComponent.h"

TileRevertCreature::TileRevertCreature(GameArena* pArena, ArenaTile* pStartTile, CreatureType type) :
	m_pArena(pArena),
	m_spTileMovementComponent(std::make_shared<TileMovementComponent>(pArena, pStartTile)),
	m_MovementDelay(1.f),
	m_CreatureType(type),
	m_SlickTexturePath("images/Slick.png"),
	m_SamTexturePath("images/Sam.png")
{}

void TileRevertCreature::Initialize()
{
	GetParent()->SetTag("SlickOrSam");

	GetParent()->AddComponent(m_spTileMovementComponent);

	// Collision
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 7.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);
	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	const std::shared_ptr<RandomAIComponent> spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena,m_MovementDelay, true, true);
	spRandomAIComponent->SetMovementAllowed(TileMovementComponent::MovementType::up, false);
	spRandomAIComponent->SetMovementAllowed(TileMovementComponent::MovementType::left, false);
	GetParent()->AddComponent(spRandomAIComponent);

	InitializeSprite();
}

void TileRevertCreature::Update()
{
	ArenaTile* pTile = m_spTileMovementComponent->GetTile();

	if (pTile->IsNullTile())
	{
		GetParent()->MarkForDelete();
	}
	else
	{
		m_spTileMovementComponent->GetTile()->Revert();
	}
}

void TileRevertCreature::OnCollisionEnter(minigen::GameObject* const other)
{
	if (other->GetTag() == "QBert")
	{
		Notify(GetParent(), minigen::Observer::Event::event_slick_sam_caught);
		GetParent()->MarkForDelete();
	}
}

void TileRevertCreature::InitializeSprite()
{
	const std::string& path = m_CreatureType == CreatureType::Slick ? m_SlickTexturePath : m_SamTexturePath;
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();
	const float scale = m_pArena->GetTileSize() / 15.f;
	imageRenderComponent->AddImage(path, { -6 * scale,-14 * scale }, scale);
	m_pParentObject->AddComponent(imageRenderComponent);
}
