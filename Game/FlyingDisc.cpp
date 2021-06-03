#include "FlyingDisc.h"

#include <iostream>



#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameArena.h"
#include "GameObject.h"
#include "ImageRenderComponent.h"

FlyingDisc::FlyingDisc(GameArena* pArena, ArenaTile* pTile) :
	m_pArena(pArena),
	m_pTile(pTile),
	m_FlyingDiscImagePath("images/FlyingDisc.png"),
	m_IsUsed(false)
{}

void FlyingDisc::Initialize()
{
	m_pParentObject->SetTag("Disc");

	InitializeSprite();

	// Create a collision subject
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 10.f * scale, 8.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .25f, -collisionSize.y * .5f, 12.f, 8.f };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);

	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);
}

void FlyingDisc::SetPosition(const Point2f& pos) const
{
	m_pParentObject->SetPosition(pos.x, pos.y);
}

void FlyingDisc::OnCollisionEnter(minigen::GameObject* const)
{
	//std::cout << "Flying disc collided with tagged object: " << pOtherGameObject->GetTag() << "\n";
	m_pParentObject->MarkForDelete();
}

void FlyingDisc::InitializeSprite()
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float scale = m_pArena->GetTileSize() / 15.f;
	const float verticalOffset = m_pArena->GetTileSize() * .1f;

	imageRenderComponent->AddImage(m_FlyingDiscImagePath, { -8 * scale,-(8.f * scale) - verticalOffset }, scale);
	AddComponent(imageRenderComponent);
}
