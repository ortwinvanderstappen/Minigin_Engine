#pragma once
#include "Component.h"

namespace minigen {
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		virtual ~RenderComponent();
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update() override = 0;
		virtual void Render() const = 0;
	};
}

