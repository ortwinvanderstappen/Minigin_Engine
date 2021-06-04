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
	const Point2f& positionOffset = m_pParentObject->GetPosition();
	for (auto image : m_spTextureMap)
	{
		const ImageEntry& entry = image.second;
		Renderer::GetInstance().RenderTexture(*image.second.texture, entry.position.x + positionOffset.x, entry.position.y + positionOffset.y, entry.scale);
	}
}

void minigen::ImageRenderComponent::AddImage(const std::string& imagePath, const Point2f& position, float scale)
{
	const std::shared_ptr<Texture2D> spTexture = ResourceManager::GetInstance().LoadTexture(imagePath);
	m_spTextureMap.insert(std::make_pair(imagePath, ImageEntry{ spTexture,position, scale }));
}

void minigen::ImageRenderComponent::RemoveImage(const std::string& imagePath)
{
	m_spTextureMap.erase(std::find_if(m_spTextureMap.begin(), m_spTextureMap.end(), 
		[imagePath](const std::pair<std::string, ImageEntry>& entry)
		{
			return entry.first == imagePath;
		}
	), m_spTextureMap.end());	
}
