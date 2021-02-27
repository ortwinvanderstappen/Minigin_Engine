#pragma once
#include "RenderComponent.h"

class ImGuiWindow;
class ImGuiComponent final : public RenderComponent
{
public:
	ImGuiComponent();
	~ImGuiComponent();

	void Render(const glm::vec3& positionOffset) const override;
	void Update() override {};

private:
	//std::vector<ImGuiWindow*> m_pGuiWindows{};
};

