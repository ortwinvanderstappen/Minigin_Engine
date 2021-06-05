#include "Coily.h"

#include <iostream>

#include "ImageRenderComponent.h"
#include "GameArena.h"
#include "ArenaTile.h"
#include "CollisionObserver.h"
#include "CollisionSubject.h"
#include "GameObject.h"
#include "GameTime.h"
#include "QBert.h"

Coily::Coily(GameArena* pArena, ArenaTile* pStartTile, const std::vector<std::shared_ptr<QBert>>& spPlayers) :
	m_pArena(pArena),
	m_spMovementComponent(std::make_shared<TileMovementComponent>(pArena, pStartTile)),
	m_spPlayers(spPlayers),
	m_CoilyBallImagePath("images/CoilyBall.png"),
	m_CoilySnakeImagePath("images/CoilySnake.png"),
	m_CoilyState(CoilyState::Ball),
	m_TransformTime(2.f),
	m_TransformTimer(0.f)
{}

void Coily::Initialize()
{
	m_pParentObject->SetTag("Coily");
	InitializeSprite();

	// Create a collision subject
	const float scale = m_pArena->GetTileSize() / 15.f;
	const Point2f collisionSize = { 8.f * scale, 4.f * scale };
	Rectf collisionBounds{ -collisionSize.x * .5f, -collisionSize.y * .5f, collisionSize.x, collisionSize.y };
	std::shared_ptr<minigen::CollisionSubject> spCollisionSubject = std::make_shared<minigen::CollisionSubject>(m_pParentObject, collisionBounds);
	m_pParentObject->SetCollisionSubject(spCollisionSubject);

	// Add observers
	const std::shared_ptr<minigen::CollisionObserver> spCollisionObserver = std::make_shared<minigen::CollisionObserver>(this);
	spCollisionSubject->AddObserver(spCollisionObserver);

	auto movedCallback = [this]() { HandleTileChange(); };
	m_spMovementComponent->SubscribeToMoved(movedCallback);

	// Movement
	m_pParentObject->AddComponent(m_spMovementComponent);
}

void Coily::InitializeSprite()
{
	const std::string& path = m_CoilyState == CoilyState::Ball ? m_CoilyBallImagePath : m_CoilySnakeImagePath;
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();
	const float scale = m_pArena->GetTileSize() / 15.f;
	imageRenderComponent->AddImage(path, { -8 * scale,-10 * scale }, scale);
	//AddComponent(imageRenderComponent);

	m_pParentObject->AddComponent(imageRenderComponent);
}

void Coily::Update()
{
	if (m_CoilyState == CoilyState::Transforming)
	{
		HandleTransformation();
	}
}

void Coily::OnCollisionEnter(minigen::GameObject* const)
{

}

void Coily::TransformIntoSnake()
{
	m_CoilyState = CoilyState::Snake;
	std::shared_ptr<minigen::ImageRenderComponent> spImageComponent = m_pParentObject->GetComponent<minigen::ImageRenderComponent>();
	if (spImageComponent)
	{
		spImageComponent->RemoveImage(m_CoilyBallImagePath);
		InitializeSprite();
	}
}

Coily::CoilyState Coily::GetState() const
{
	return m_CoilyState;
}

void Coily::CheckTransformation()
{
	// Coily should start transforming if he reaches the bottom tile
	if (m_pArena->IsBottomTileIndex(m_spMovementComponent->GetTile()->GetIndex()))
	{
		m_CoilyState = CoilyState::Transforming;
	}
}

void Coily::HandleTransformation()
{
	const float deltaTime = Time::GetInstance().DeltaTime();

	m_TransformTimer += deltaTime;
	if (m_TransformTimer >= m_TransformTime)
	{
		TransformIntoSnake();
	}
}

void Coily::HandleTileChange()
{
	if (m_spMovementComponent->GetTile()->IsNullTile())
	{
		Notify(GetParent(), minigen::Observer::Event::event_coily_fall);
		m_pParentObject->MarkForDelete();
	}
	else if (m_CoilyState == CoilyState::Ball)
	{
		CheckTransformation();
	}
}
