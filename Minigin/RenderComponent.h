#pragma once
#include <glm/detail/type_vec.hpp>

#include "Component.h"

class RenderComponent : public Component
{
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void FixedUpdate() override = 0;
	virtual void Render(const glm::vec3& positionOffset) const = 0;
};

