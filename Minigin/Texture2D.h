#pragma once
#include <SDL_surface.h>
#include <GL/gl.h>

#include "structs.h"

struct SDL_Texture;
namespace minigen
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		Texture2D(SDL_Surface* pSurface);
		~Texture2D();

		void Draw(const Rectf& dstRect, const Rectf& srcRect, float scale) const;
		
		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		void CreateFromSurface(SDL_Surface* pSurface);
		
		bool m_CreationOk = true;
		float m_Width;
		float m_Height;
		GLuint m_Id = 0;
	};
}
