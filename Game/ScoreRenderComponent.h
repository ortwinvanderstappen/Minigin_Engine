#pragma once
#include <RenderComponent.h>
#include <structs.h>

class ScoreRenderComponent : public minigen::RenderComponent
{
public:
	ScoreRenderComponent(const Point2f& position);
	
	void Update() override {};
	void Render() const override;

private:
	Point2f m_Position;
};

