#pragma once
#include "Transform.h"

namespace minigen
{
	class Font;
	class Texture2D;
	class TextObject final
	{
	public:
		void Update();
		void Render(const Point2f& positionOffset) const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		explicit TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;

		Transform m_Transform;
	};
}
