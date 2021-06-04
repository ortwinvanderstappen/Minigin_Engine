#include "MiniginPCH.h"
#include "ButtonComponent.h"

#include <SDL_mouse.h>

minigen::ButtonComponent::ButtonComponent(const Rectf& buttonTransform) :
	m_ButtonTransform(buttonTransform)
{

}

void minigen::ButtonComponent::Update()
{
	Point2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	//std::cout << "mousepos: [ " << mousePos.x << ", " << mousePos.y << " ] \n";

	if(IsMouseOnButton(mousePos))
	{
		std::cout << "Mouse is on button \n";
	}
}

bool minigen::ButtonComponent::IsMouseOnButton(const Point2i& mousePos) const
{
	return (static_cast<float>(mousePos.x) >= m_ButtonTransform.x && static_cast<float>(mousePos.x) <= m_ButtonTransform.x + m_ButtonTransform.w) &&
		(static_cast<float>(mousePos.y) >= m_ButtonTransform.y && static_cast<float>(mousePos.y) <= m_ButtonTransform.y + m_ButtonTransform.h);
}
