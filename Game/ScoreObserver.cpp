#include "ScoreObserver.h"

#include <SDL_render.h>
#include "Renderer.h"

void ScoreObserver::Notify(minigen::GameObject*, Event event)
{
	switch (event)
	{
	case Event::event_tile_color_change:
		m_Score += 25;
		break;
	case Event::event_coily_fall:
		m_Score += 500;
		break;
	case Event::event_stage_complete:
		// TODO: check how many flying discs are left...
		break;
	case Event::event_slick_sam_caught:
		m_Score += 300;
		break;
	default:;
	}
}
//
//void ScoreObserver::Update()
//{}
//
//void ScoreObserver::Render() const
//{
//	int width; int height;
//	SDL_GetRendererOutputSize(minigen::Renderer::GetInstance().GetSDLRenderer(), &width, &height);
//
//	ImGui::Begin("Score", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
//	ImGui::SetWindowFontScale(1.3f);
//	ImGui::SetWindowPos(ImVec2{ static_cast<float>(width) * .5f + 100.f,50.f });
//	ImGui::Text("Score %i", GetScore());
//	ImGui::End();
//}

int ScoreObserver::GetScore() const
{
	return m_Score;
}

void ScoreObserver::ResetScore()
{
	m_Score = 0;
}
