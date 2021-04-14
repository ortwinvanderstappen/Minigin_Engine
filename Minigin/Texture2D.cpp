#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

minigen::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* minigen::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

minigen::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
