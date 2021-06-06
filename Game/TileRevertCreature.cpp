#include "stdafx.h"
#include "TileRevertCreature.h"

#include <CollisionObserver.h>
#include <CollisionSubject.h>
#include <ImageRenderComponent.h>

#include "GameArena.h"
#include "GameContext.h"
#include "RandomAIComponent.h"
#include "TileMovementComponent.h"

TileRevertCreature::TileRevertCreature(GameArena* pArena, ArenaTile* pStartTile, CreatureType type) :
	m_pArena(pArena),
	m_pStartTile(pStartTile),
	m_spTileMovementComponent(nullptr),
	m_CreatureType(type),
	m_SlickTexturePath("images/Slick.png"),
	m_SamTexturePath("images/Sam.png")
{}

void TileRevertCreature::Initialize()
{
	GetParent()->SetTag("SlickOrSam");

	m_spTileMovementComponent = std::make_shared<TileMovementComponent>(m_pStartTile,
		GameContext::GetInstance().GetEntityProperty(EntityType::slickOrSam)->movespeed, true);
	GetParent()->AddComponent(m_spTileMovementComponent);
	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upRight, false);
	m_spTileMovementComponent->SetMovementAllowed(TileMovementComponent::MovementType::upLeft, false);

	// Collision
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 7.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);
	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	const float aiWaitTime = GameContext::GetInstance().GetEntityProperty(EntityType::slickOrSam)->aiWaitTime;
	const std::shared_ptr<RandomAIComponent> spRandomAIComponent = std::make_shared<RandomAIComponent>(m_pArena, aiWaitTime, true, true);
	GetParent()->AddComponent(spRandomAIComponent);

	auto movedCallback = [this]() { HandleTileChange(); };
	m_spTileMovementComponent->SubscribeToMoveCompleted(movedCallback);

	InitializeSprite();
}

void TileRevertCreature::Update()
{

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

void TileRevertCreature::HandleTileChange()
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
