#include "MiniginPCH.h"
#include "Font.h"

#include <SDL_ttf.h>

TTF_Font* minigen::Font::GetFont() const {
	return m_Font;
}

minigen::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

minigen::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
