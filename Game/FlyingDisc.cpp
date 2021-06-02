#include "FlyingDisc.h"


#include "GameObject.h"
#include "ImageRenderComponent.h"

FlyingDisc::FlyingDisc() :
	m_FlyingDiscImagePath("images/FlyingDisc.png"),
	m_IsUsed(false)
{}

void FlyingDisc::Initialize()
{
	InitializeSprite();
}

void FlyingDisc::SetPosition(const Point2f& pos) const
{
	m_pParentObject->SetPosition(pos.x, pos.y);
}

void FlyingDisc::InitializeSprite()
{
	std::shared_ptr<minigen::ImageRenderComponent> imageRenderComponent = std::make_shared<minigen::ImageRenderComponent>();

	const float scale = 2.f;
	imageRenderComponent->AddImage(m_FlyingDiscImagePath, { -8 * scale,-8 * scale }, scale);
	AddComponent(imageRenderComponent);
}
