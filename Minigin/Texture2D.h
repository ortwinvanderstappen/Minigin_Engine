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
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		void CreateFromSurface(SDL_Surface* pSurface);
		void Draw(const Rectf& dstRect, const Rectf& srcRect ) const;
		
		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_Texture;

		bool m_CreationOk = true;
		float m_Width;
		float m_Height;
		GLuint m_Id = 0;
	};
}
