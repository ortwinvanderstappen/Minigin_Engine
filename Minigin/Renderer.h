#pragma once
#include <SDL_video.h>

#include "Singleton.h"
#include "structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace minigen
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, float scale = 1.f) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderPolygon(const std::vector<Point2f>& points, const Color3f& color) const;
		void RenderRect(const Rectf& rect, const Color3f& color);
		
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window * m_Window = nullptr;
		SDL_GLContext m_Context = nullptr;

		bool m_ShowDemo = true;
	};
}

