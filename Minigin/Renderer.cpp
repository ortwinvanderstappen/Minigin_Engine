#include "MiniginPCH.h"
#include "Renderer.h"

#include <imgui.h>
#include <SDL.h>
#include <backends/imgui_impl_opengl2.h>
#include <backends/imgui_impl_sdl.h>
#include <GL/gl.h>

#include "SceneManager.h"
#include "Texture2D.h"

minigen::Renderer::Renderer() :
	m_Width(0),
	m_Height(0)
{}

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

	// Obtain window size
	SDL_GetRendererOutputSize(m_Renderer, &m_Width, &m_Height);

	SDL_RendererInfo displayRendererInfo;
	SDL_GetRendererInfo(m_Renderer, &displayRendererInfo);
	if ((displayRendererInfo.flags & SDL_RENDERER_ACCELERATED) == 0 || (displayRendererInfo.flags & SDL_RENDERER_TARGETTEXTURE) == 0)
	{
		std::cout << "No correct render flags\n";
	}

	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	ImGuiIO& imGuiIo = ImGui::GetIO();
	ImFont* pFont = imGuiIo.Fonts->AddFontFromFileTTF("Data/DiaryOfAn8BitMage-lYDD.ttf", 22);
	imGuiIo.FontDefault = pFont;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_Width, 0, m_Height, 0, 1000);
	glViewport(0, 0, m_Width, m_Height);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void minigen::Renderer::Render() const
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_Width, m_Height, 0, -1, 1);

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

void minigen::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, float scale) const
{
	const Rectf dstRect{ x, y, 0, 0 };
	const Rectf srcRect{};
	texture.Draw(dstRect, srcRect, scale);
}

void minigen::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	const Rectf dstRect{ x, y, width, height };
	const Rectf srcRect{};
	texture.Draw(dstRect, srcRect, 1.f);
}

void minigen::Renderer::RenderPolygon(const std::vector<Point2f>& points, const Color3f& color) const
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POLYGON);
	{
		for (size_t i = 0; i < points.size(); ++i)
		{
			glVertex2f(points[i].x, points[i].y);
		}
	}
	glEnd();
}

void minigen::Renderer::RenderRect(const Rectf& rect, const Color3f& color)
{
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_QUADS);
	{
		glVertex2f(rect.x, rect.y);
		glVertex2f(rect.x + rect.w, rect.y);
		glVertex2f(rect.x + rect.w, rect.y + rect.h);
		glVertex2f(rect.x, rect.y + rect.h);
	}
	glEnd();
}
