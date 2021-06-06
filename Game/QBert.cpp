#include "stdafx.h"
#include "QBert.h"

#include <CollisionObserver.h>
#include <CollisionSubject.h>
#include <GameObject.h>
#include <ImageRenderComponent.h>
#include <InputComponent.h>
#include <SoundComponent.h>

#include "ArenaTile.h"
#include "GameArena.h"

QBert::QBert(GameArena* pArena, ArenaTile* pStartTile) :
	m_pArena(pArena),
	m_pSpawnTile(pStartTile),
	m_spTileMovementComponent(std::make_shared<TileMovementComponent>(pArena, pStartTile)),
	m_QbertImagePath("images/QBert.png")
{}

void QBert::Initialize()
{
	m_pParentObject->SetTag("QBert");

	InitializeSprite();
	InitializeSounds();

	// Create a collision subject
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 7.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);

	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	auto movedCallback = [this]() { HandleTileChange(); };
	m_spTileMovementComponent->SubscribeToMoveCompleted(movedCallback);

	auto moveCallback = [this]() { HandleMove(); };
	m_spTileMovementComponent->SubscribeToMove(moveCallback);

	// Movement
	m_pParentObject->AddComponent(m_spTileMovementComponent);
}

void QBert::InitializeSprite() const
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float scale = m_pArena->GetTileSize() / 15.f;
	imageRenderComponent->AddImage(m_QbertImagePath, { -8 * scale,-16 * scale }, scale);
	m_pParentObject->AddComponent(imageRenderComponent);
}

void QBert::InitializeSounds()
{
	using namespace minigen;

	std::string basePath{ "Data/audio/" };

	m_spDeathSoundComponent = std::make_shared<SoundComponent>(basePath + "QBertDie.wav");
	m_spFallSoundComponent = std::make_shared<SoundComponent>(basePath + "QBertFall.wav");
	m_spJumpSoundComponent = std::make_shared<SoundComponent>(basePath + "QBertJump.wav");
	m_spLiftSoundComponent = std::make_shared<SoundComponent>(basePath + "QBertLift.wav");

	GetParent()->AddComponent(m_spDeathSoundComponent);
}

void QBert::Die()
{
	Notify(GetParent(), minigen::Observer::Event::event_qbert_death);
}

void QBert::HandleTileChange()
{
	ArenaTile* pTile = m_spTileMovementComponent->GetTile();

	if (pTile->IsNullTile() && !pTile->HasDisc())
	{
		m_spFallSoundComponent->PlaySoundEffect();
		Die();

		// Reset QBerts position
		m_spTileMovementComponent->SpawnOnTile(m_pSpawnTile);
	}
	else
	{
		pTile->Activate();
	}
}

void QBert::HandleMove() const
{
	m_spJumpSoundComponent->PlaySoundEffect();
}

void QBert::OnCollisionEnter(minigen::GameObject* const pOtherGameObject)
{
	if (pOtherGameObject->GetTag() == "Disc")
	{
		m_spLiftSoundComponent->PlaySoundEffect();
		const float delay = 2.3f;
		m_pArena->ResetStageEntities(delay);

		m_spTileMovementComponent->CompleteMovement();
		m_spTileMovementComponent->MoveToTile(m_pArena->GetTopTile(), true, -2.4f);
	}
	else if (pOtherGameObject->GetTag() == "Coily" || pOtherGameObject->GetTag() == "Ugg" || pOtherGameObject->GetTag() == "Wrongway")
	{
		m_spDeathSoundComponent->PlaySoundEffect();
		Die();
	}
}
