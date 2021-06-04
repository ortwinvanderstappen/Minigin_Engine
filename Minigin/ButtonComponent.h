#pragma once
#include "Component.h"
#include "structs.h"

namespace minigen {
	class ButtonComponent :public Component
	{
	public:
		ButtonComponent(const Rectf& buttonTransform);
		void Update() override;
	private:
		bool IsMouseOnButton(const Point2i& mousePos) const;
		Rectf m_ButtonTransform;
	};
}

