#include "MiniginPCH.h"
#include "ImGuiComponent.h"
//#include "ImGuiWindow.h"

//#include <glm/detail/type_vec3.hpp>
#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

ImGuiComponent::ImGuiComponent()
{}

ImGuiComponent::~ImGuiComponent()
{
	//for(ImGuiWindow* pWindow: m_pGuiWindows)
	//{
	//	delete pWindow;
	//}
	//m_pGuiWindows.clear();
}

void ImGuiComponent::Render(const glm::vec3& positionOffset) const
{
	// TODO: remove
	glm::vec3 binPos = positionOffset;
	binPos.x += 1;

	//for(ImGuiWindow* pWindow: m_pGuiWindows)
	//{
	//	pWindow->Render();
	//}

	//ImGui::Begin("Test window");
	//ImGui::SetWindowPos(ImVec2{0.f,75.f});

	//ImGui::Text("This is the test window.");
	//ImGui::Separator();
	//ImGui::Text("ImGui fps: %.1f", 1000.0f /  ImGui::GetIO().Framerate);
	//ImGui::Separator();
	//
	//ImGui::End();
}
