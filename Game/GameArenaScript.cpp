#include "GameArenaScript.h"

#include <iostream>
#include <SDL_render.h>

#include "ArenaHexScript.h"
#include "Renderer.h"
#include "structs.h"

GameArenaScript::GameArenaScript(int baseWidth) :
	RenderComponent(),
	m_BaseWidth(baseWidth)
{
	Initialize();
}

GameArenaScript::~GameArenaScript()
{}

void GameArenaScript::Initialize()
{
	InitializeArena();
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
	const int offsetX = static_cast<int>(static_cast<float>(sqrt(3)) * hexSize);
	const int offsetY = static_cast<int>(2 * hexSize);
	const int totalWidthNeeded = offsetX * m_BaseWidth;
	const Point2i startPos{ ((width - totalWidthNeeded) / 2) + (offsetX / 2), height - offsetY };
	Point2i currentPos{ startPos };

	// Initialize hex grids
	for (int row = 0; row < m_BaseWidth; ++row)
	{
		for (int column = 0; column < m_BaseWidth; ++column)
		{
			if (!(column - row >= 0)) continue;

			ArenaHexScript hex{ this, row, column, hexSize, currentPos };
			m_ArenaHexex.push_back(std::move(hex));
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
	for(const ArenaHexScript& hex: m_ArenaHexex)
	{
		hex.Render();
	}
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
