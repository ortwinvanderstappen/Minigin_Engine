#pragma once
#include "TextRenderComponent.h"

class FPSComponent;

class FPSComponent final : public TextRenderComponent
{
public:
	FPSComponent();

	void Update() override;
	const int& GetFPS() const;
private:
	float m_TimePassed = 0.f;
	int m_Framecount = 0;
	int m_CurrentFPS = 0;

	int m_FrameHistoryCount = 10;
	std::vector<int> m_FpsHistory;
};
