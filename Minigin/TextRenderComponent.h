#pragma once
#include "RenderComponent.h"
#include "TextObject.h"
#include "structs.h"
#include "unordered_map"

namespace minigen {
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent();

		void AddText(int id, const std::string& text, const Point2f& position, int fontSize);
		void SetText(int id, const std::string& newText);
		void SetPosition(int id, const Point2f& newPosition);
		virtual void Update() override;
		void Render(const glm::vec3& positionOffset) const override;

	protected:
		std::unordered_map<int, std::shared_ptr<TextObject>> m_upTextObjectMap{};
	private:
		Font* m_pFont = nullptr;
	};
}

