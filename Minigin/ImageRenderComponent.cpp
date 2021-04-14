#include "MiniginPCH.h"
#include "ImageRenderComponent.h"
//#include <glm/detail/type_vec3.hpp>
#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm/glm.hpp>
#pragma warning(pop)

#include "Renderer.h"
#include "ResourceManager.h"

ImageRenderComponent::ImageRenderComponent() 
{}

void ImageRenderComponent::Update()
{

}

void ImageRenderComponent::Render(const glm::vec3& positionOffset) const
{
	for (auto image : m_spTextureMap)
	{
		minigen::Renderer::GetInstance().RenderTexture(*image.second.second,
			image.second.first.x + positionOffset.x, image.second.first.y + positionOffset.y);
	}
}

void ImageRenderComponent::AddImage(const std::string& imagePath, const Point2f& position)
{
	std::shared_ptr<minigen::Texture2D> spTexture = minigen::ResourceManager::GetInstance().LoadTexture(imagePath);
	m_spTextureMap.insert(std::make_pair(imagePath, std::make_pair(position, spTexture)));

}
