#include "MiniginPCH.h"
#include "ButtonComponent.h"

#include <SDL_mouse.h>

minigen::ButtonComponent::ButtonComponent(const Rectf& buttonTransform) :
	m_ButtonTransform(buttonTransform)
{

}

void minigen::ButtonComponent::Update()
{
}

void minigen::ButtonComponent::MouseClick() const
{
	Point2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if(IsMouseOnButton(mousePos))
	{
		if(m_ButtonCallback)
		{
			m_ButtonCallback();
		}
	}
}

void minigen::ButtonComponent::SetCallback(ButtonCallback callback)
{
	m_ButtonCallback = callback;
}

bool minigen::ButtonComponent::IsMouseOnButton(const Point2i& mousePos) const
{
	return (static_cast<float>(mousePos.x) >= m_ButtonTransform.x && static_cast<float>(mousePos.x) <= m_ButtonTransform.x + m_ButtonTransform.w) &&
		(static_cast<float>(mousePos.y) >= m_ButtonTransform.y && static_cast<float>(mousePos.y) <= m_ButtonTransform.y + m_ButtonTransform.h);
}
