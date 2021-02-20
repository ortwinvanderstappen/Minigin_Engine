#pragma once
#include "SceneObject.h"

namespace dae
{
	class Texture2D;
	class GameObject final: public SceneObject
	{
	public:
		virtual void FixedUpdate() override;
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
	};

}
