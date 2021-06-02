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
		void Render() const override;

		void AddImage(const std::string& imagePath, const Point2f& position = { 0.f,0.f }, float scale = 1.f);

	private:
		struct ImageEntry
		{
			std::shared_ptr<Texture2D> texture;
			Point2f position;
			float scale;
		};
		
		std::unordered_map<std::string, ImageEntry> m_spTextureMap{};
	};
}

