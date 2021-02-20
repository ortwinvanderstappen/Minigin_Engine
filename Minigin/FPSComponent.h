#pragma once
#include "Component.h"
#include "TextRenderComponent.h"

class FPSComponent;

class FPSComponent final : public TextRenderComponent
{
public:
	FPSComponent(const Point2f& position);

	void Update() override;
	const int& GetFPS() const;
private:
	float m_TimePassed = 0.f;
	int m_Framecount = 0;
	int m_CurrentFPS = 0;
};
