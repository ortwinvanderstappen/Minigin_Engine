#pragma once
//#include <glm/detail/type_vec.hpp>
#pragma warning (push)
#pragma warning(disable: 4201)
#include <glm.hpp>
#pragma warning(pop)

#include "Component.h"
#include "imgui.h"

namespace minigen {
	class RenderComponent : public Component
	{
	public:
		RenderComponent();
		virtual ~RenderComponent();

		virtual void Update() override = 0;
		virtual void Render(const glm::vec3& positionOffset) const = 0;
	};
}

