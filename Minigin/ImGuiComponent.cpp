#include "MiniginPCH.h"
#include "ImGuiComponent.h"
//#include "ImGuiWindow.h"

//#include <glm/detail/type_vec3.hpp>
#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

minigen::ImGuiComponent::ImGuiComponent()
{}

minigen::ImGuiComponent::~ImGuiComponent()
{
	//for(ImGuiWindow* pWindow: m_pGuiWindows)
	//{
	//	delete pWindow;
	//}
	//m_pGuiWindows.clear();
}

void minigen::ImGuiComponent::Render() const
{
	//for(ImGuiWindow* pWindow: m_pGuiWindows)
	//{
	//	pWindow->Render();
	//}

	ImGui::Begin("Test window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos(ImVec2{0.f,75.f});

	ImGui::Text("This is the test window.");
	ImGui::Separator();
	ImGui::Text("ImGui fps: %.1f", ImGui::GetIO().Framerate);
	ImGui::Separator();
	
	ImGui::End();
}
