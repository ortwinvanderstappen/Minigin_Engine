#pragma once
#include "Component.h"

namespace minigen {
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		virtual ~RenderComponent();

		virtual void Update() override = 0;
		virtual void Render() const = 0;
	};
}

