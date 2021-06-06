#include "MiniginPCH.h"
#include "TextRenderComponent.h"

#include <algorithm>

#include "GameObject.h"
#include "ResourceManager.h"

minigen::TextRenderComponent::TextRenderComponent()
{}

void minigen::TextRenderComponent::AddText(int id, const std::string& text, const Point2f& position, int fontSize)
{
	std::shared_ptr<Font> const pFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	std::shared_ptr<TextObject> spTextObject = std::make_shared<TextObject>(text, pFont);
	spTextObject->SetPosition(position.x, position.y);
	m_upTextObjectMap.insert(std::make_pair(id, spTextObject));
}

void minigen::TextRenderComponent::SetText(int id, const std::string& newText)
{
	if (m_upTextObjectMap.find(id) != m_upTextObjectMap.end())
	{
		m_upTextObjectMap[id]->SetText(newText);
	}
}

void minigen::TextRenderComponent::SetPosition(int id, const Point2f& newPosition)
{
	if (m_upTextObjectMap.find(id) != m_upTextObjectMap.end())
	{
		m_upTextObjectMap[id]->SetPosition(newPosition.x, newPosition.y);
	}
}

void minigen::TextRenderComponent::Update()
{
	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [](std::pair<int, std::shared_ptr<minigen::TextObject>> textPair)
		{
			textPair.second->Update();
		}
	);
}

void minigen::TextRenderComponent::Render() const
{
	const Point2f& pos = m_pParentObject->GetPosition();
	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [pos](std::pair<int, std::shared_ptr<minigen::TextObject>> textPair)
		{
			textPair.second->Render(pos);
		}
	);
}
