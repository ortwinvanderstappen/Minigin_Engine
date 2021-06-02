#include "MiniginPCH.h"
#include "ImageRenderComponent.h"
//#include <glm/detail/type_vec3.hpp>
#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"

minigen::ImageRenderComponent::ImageRenderComponent() 
{}

void minigen::ImageRenderComponent::Update()
{

}

void minigen::ImageRenderComponent::Render() const
{
	const glm::vec3& positionOffset = m_pParentObject->GetPosition();
	for (auto image : m_spTextureMap)
	{
		Renderer::GetInstance().RenderTexture(*image.second.second, image.second.first.x + positionOffset.x, image.second.first.y + positionOffset.y);
	}
}

void minigen::ImageRenderComponent::AddImage(const std::string& imagePath, const Point2f& position)
{
	std::shared_ptr<Texture2D> spTexture = ResourceManager::GetInstance().LoadTexture(imagePath);
	m_spTextureMap.insert(std::make_pair(imagePath, std::make_pair(position, spTexture)));
}
