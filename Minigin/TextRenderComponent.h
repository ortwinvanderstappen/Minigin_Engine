#pragma once
#include <unordered_map>

#include "RenderComponent.h"
#include "structs.h"
#include "TextObject.h"

namespace minigen {
	class TextRenderComponent : public RenderComponent
	{
	public:
		TextRenderComponent();
		TextRenderComponent(const TextRenderComponent& other) = delete;
		TextRenderComponent(TextRenderComponent&& other) = delete;
		TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
		TextRenderComponent& operator=(TextRenderComponent&& other) = delete;

		void AddText(int id, const std::string& text, const Point2f& position, int fontSize);
		void SetText(int id, const std::string& newText);
		void SetPosition(int id, const Point2f& newPosition);
		virtual void Update() override;
		void Render() const override;

	protected:
		std::unordered_map<int, std::shared_ptr<TextObject>> m_upTextObjectMap{};
	private:
		Font* m_pFont = nullptr;
	};
}

