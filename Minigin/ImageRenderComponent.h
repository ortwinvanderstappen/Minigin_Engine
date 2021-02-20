#pragma once
#include "RenderComponent.h"
#include "structs.h"
#include "Texture2D.h"
#include "unordered_map"
class ImageRenderComponent final :public RenderComponent
{
public:
	ImageRenderComponent();

	void FixedUpdate() override;
	void Render(const glm::vec3& positionOffset) const override;

	void AddImage(const std::string& imagePath, const Point2f& position = { 0.f,0.f });

private:
	std::unordered_map<std::string,
		std::pair<const Point2f, std::shared_ptr<dae::Texture2D>>> m_spTextureMap{};
};

