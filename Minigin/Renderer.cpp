#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include <GL/gl.h>


#include "imgui.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void minigen::Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_Context = SDL_GL_CreateContext(m_Window);

	SDL_RendererInfo displayRendererInfo;
	SDL_GetRendererInfo(m_Renderer, &displayRendererInfo);
	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 || (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
	{
		std::cout << "No correct render flags\n";
	}
	//glEnable(GL_TEXTURE_2D);

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void minigen::Renderer::Render() const
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1, 1);
	
	// Render ImGui demo window
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(m_Window);
}

void minigen::Renderer::Destroy()
{
	// Destroy ImGui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_GL_DeleteContext(m_Context);
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void minigen::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	//SDL_Rect dst;
	//dst.x = static_cast<int>(x);
	//dst.y = static_cast<int>(y);
	//SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);

	Rectf dstRect{ x, y, 0, 0 };
	Rectf srcRect{};
	texture.Draw(dstRect, srcRect);
}

void minigen::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	//SDL_Rect dst;
	//dst.x = static_cast<int>(x);
	//dst.y = static_cast<int>(y);
	//dst.w = static_cast<int>(width);
	//dst.h = static_cast<int>(height);
	//SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);

	Rectf dstRect{ x, y, width, height };
	Rectf srcRect{};
	texture.Draw(dstRect, srcRect);
}

void minigen::Renderer::RenderPolygon(const std::vector<Point2i>& points, const Color3f& color) const
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	{
		for (int i = 0; i < points.size(); ++i)
		{
			glVertex2f(float(points[i].x), float(points[i].y));
		}
	}
	glEnd();
}
