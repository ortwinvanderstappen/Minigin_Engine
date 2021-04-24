#pragma once
#include "RenderComponent.h"
#include "structs.h"
#include "unordered_map"

namespace minigen {
	class Texture2D;
	class ImageRenderComponent final: public RenderComponent
	{
	public:
		ImageRenderComponent();

		void Update() override;
		void Render(const glm::vec3& positionOffset) const override;

		void AddImage(const std::string& imagePath, const Point2f& position = { 0.f,0.f });

	private:
		std::unordered_map<std::string, std::pair<const Point2f, std::shared_ptr<Texture2D>>> m_spTextureMap{};
	};
}

