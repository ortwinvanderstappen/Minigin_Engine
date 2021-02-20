#include "MiniginPCH.h"
#include "TextRenderComponent.h"

#include "ResourceManager.h"
#include <algorithm>

TextRenderComponent::TextRenderComponent()
{
}

void TextRenderComponent::AddText(int id, const std::string& text, const Point2f& position, int fontSize)
{
	std::shared_ptr<dae::Font> const pFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize);
	std::shared_ptr<dae::TextObject> spTextObject = std::make_shared<dae::TextObject>(text, pFont);
	spTextObject->SetPosition(position.x, position.y);
	m_upTextObjectMap.insert(std::make_pair(id,spTextObject));
}

void TextRenderComponent::SetText(int id, const std::string& newText)
{
	if (m_upTextObjectMap.find(id) != m_upTextObjectMap.end())
	{
		m_upTextObjectMap[id]->SetText(newText);
	}
}

void TextRenderComponent::SetPosition(int id, const Point2f& newPosition)
{
	if (m_upTextObjectMap.find(id) != m_upTextObjectMap.end())
	{
		m_upTextObjectMap[id]->SetPosition(newPosition.x, newPosition.y);
	}
}

void TextRenderComponent::FixedUpdate()
{
	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [](std::pair<int, std::shared_ptr<dae::TextObject>> textPair)
		{
			textPair.second->FixedUpdate();
		}
	);
}

void TextRenderComponent::Render(const glm::vec3& positionOffset) const
{
	std::for_each(m_upTextObjectMap.begin(), m_upTextObjectMap.end(), [positionOffset](std::pair<int, std::shared_ptr<dae::TextObject>> textPair)
		{
			textPair.second->Render(positionOffset);
		}
	);
}
