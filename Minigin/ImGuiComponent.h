#pragma once
#include "RenderComponent.h"

namespace minigen {
	class ImGuiWindow;
	class ImGuiComponent final : public RenderComponent
	{
	public:
		ImGuiComponent();
		~ImGuiComponent();

		void Render() const override;
		void Update() override {};

	private:
		//std::vector<ImGuiWindow*> m_pGuiWindows{};
	};
}

