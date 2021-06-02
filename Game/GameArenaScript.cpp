#include "GameArenaScript.h"

#include <iostream>
#include <SDL_render.h>

#include "ArenaHexScript.h"
#include "GameObject.h"
#include "QBertScript.h"
#include "Renderer.h"
#include "Scene.h"
#include "structs.h"

GameArenaScript::GameArenaScript(const GameScene::StageSettings& stageSettings) :
	m_BaseWidth(stageSettings.size),
	m_PrimaryColor(stageSettings.activeColor),
	m_SecondaryColor(stageSettings.inactiveColor)
{}

GameArenaScript::~GameArenaScript()
{}

void GameArenaScript::Initialize()
{
	InitializeArena();
	AddPlayer();
}

void GameArenaScript::InitializeArena()
{
	using namespace minigen;
	SDL_Renderer* pRenderer = Renderer::GetInstance().GetSDLRenderer();

	// Obtain window size
	int width; int height;
	SDL_GetRendererOutputSize(pRenderer, &width, &height);

	// Calculate hex size
	const float hexSize = static_cast<float>(std::min(width, height)) / static_cast<float>(m_BaseWidth * 2);

	// Calculate the start position based on hex sizes and screen size
	const float offsetX = static_cast<float>(sqrt(3)) * hexSize;
	const float offsetY = 2 * hexSize;
	const float totalWidthNeeded = offsetX * m_BaseWidth;
	const Point2f startPos{ ((width - totalWidthNeeded) / 2.f) + (offsetX / 2.f), height - offsetY };
	Point2f currentPos{ startPos };

	// Initialize hex grids
	for (int row = 0; row < m_BaseWidth; ++row)
	{
		for (int column = 0; column < m_BaseWidth; ++column)
		{
			if (!(column - row >= 0)) continue;

			ArenaHexScript hex{ this, row, column, hexSize, currentPos };
			m_ArenaHexes.push_back(std::move(hex));
			currentPos.x += offsetX;
		}
		// row is done, reset x position
		currentPos.x = startPos.x + (offsetX / 2) * (row + 1);
		currentPos.y -= static_cast<int>(static_cast<float>(offsetY) * .75f);
	}
}

void GameArenaScript::Update()
{}

void GameArenaScript::Render() const
{
	for (const ArenaHexScript& hex : m_ArenaHexes)
	{
		hex.Render();
	}
}

void GameArenaScript::AddPlayer()
{
	std::shared_ptr<minigen::GameObject> QBert = std::make_shared<minigen::GameObject>();
	const std::shared_ptr<QBertScript> QbertComponent = std::make_shared<QBertScript>(0);
	QBert->AddScript(QbertComponent);
	m_pParentObject->GetScene()->Add(QBert);

	const Point2f& startPos = m_ArenaHexes[m_ArenaHexes.size() - 1].GetCenter();
	QBert->SetPosition(startPos.x, startPos.y);
}

const Color3i& GameArenaScript::GetPrimaryColor() const
{
	return m_PrimaryColor;
}

const Color3i& GameArenaScript::GetSecondaryColor() const
{
	return m_SecondaryColor;
}

int GameArenaScript::CalculateArenaHexCount() const
{
	int base = m_BaseWidth;
	int count = 0;
	while (base > 0)
	{
		count += base;
		base -= 1;
	}
	return count;
}
