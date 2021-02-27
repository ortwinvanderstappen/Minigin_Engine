#pragma once
#include <glm/detail/type_vec.hpp>

#include "Component.h"
#include "Transform.h"

#include <memory>

namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update() = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;

	protected:
	};

}
