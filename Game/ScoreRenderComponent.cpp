#include "ScoreRenderComponent.h"

#include <SDL_render.h>
#include "GameContext.h"
#include "Renderer.h"
#include "ScoreObserver.h"

ScoreRenderComponent::ScoreRenderComponent(const Point2f& position) :
	m_Position(position)
{}

void ScoreRenderComponent::Render() const
{
	int width; int height;
	SDL_GetRendererOutputSize(minigen::Renderer::GetInstance().GetSDLRenderer(), &width, &height);

	int score = -1;

	const std::shared_ptr<ScoreObserver>& spScoreObserver = GameContext::GetInstance().GetScoreObserver();
	if (spScoreObserver)
		score = spScoreObserver->GetScore();

	ImGui::Begin("Score", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SetWindowPos(ImVec2{ m_Position.x - (ImGui::GetFontSize() * 3.2f) ,m_Position.y });
	ImGui::Text("Score %i", score);
	ImGui::End();
}
