#include "MiniginPCH.h"
#include "MouseObserver.h"

#include "ButtonComponent.h"
#include "GameObject.h"
#include "Scene.h"

minigen::MouseObserver::MouseObserver(std::shared_ptr<ButtonComponent> spButton) :
	m_wpButton(spButton)
{}

void minigen::MouseObserver::Notify(GameObject*, Event event)
{
	if (event == Event::mouse_click)
	{
		const std::shared_ptr<ButtonComponent> spButton = m_wpButton.lock();
		if (spButton)
		{
			if (spButton->GetParent()->GetScene()->IsActive())
				spButton->MouseClick();
		}
	}
}
