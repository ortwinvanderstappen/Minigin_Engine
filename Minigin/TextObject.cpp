#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"

#include <GL/gl.h>

#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

minigen::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), m_Transform{}
{}

void minigen::TextObject::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now

		// Load the text with the font
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		//// Create SDL texture from surface
		//auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		//if (texture == nullptr)
		//{
		//	throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		//}
		
		// Store the texture
		m_Texture = std::make_shared<Texture2D>(nullptr);
		m_Texture->CreateFromSurface(surf);
				
		// Free up the surface
		SDL_FreeSurface(surf);
		m_NeedsUpdate = false;
	}
}

void minigen::TextObject::Render(const glm::vec3& positionOffset) const
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Transform.GetPosition() + positionOffset;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void minigen::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void minigen::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}


