#pragma once
#include <functional>

#include "Component.h"
#include "structs.h"

namespace minigen {
	class ButtonComponent :public Component
	{
	public:
		typedef std::function<void()> ButtonCallback;

		ButtonComponent(const Rectf& buttonTransform);
		void Update() override;

		void MouseClick() const;
		
	void SetCallback(ButtonCallback callback);
	private:
		bool IsMouseOnButton(const Point2i& mousePos) const;
		Rectf m_ButtonTransform;
		ButtonCallback m_ButtonCallback;
	};
}

