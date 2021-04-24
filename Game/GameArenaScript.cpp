#include "GameArenaScript.h"

#include <iostream>
#include <SDL_render.h>
#include "helper.h"
#include "Renderer.h"
#include "structs.h"

GameArenaScript::GameArenaScript(int baseWidth) :
	RenderComponent(),
	m_BaseWidth(baseWidth)
{
	Initialize();
}

GameArenaScript::~GameArenaScript()
{
	delete[] pArena;
	pArena = nullptr;
}

void GameArenaScript::Initialize()
{
	// Arena size
	const int size = CalculateArenaHexCount();
	pArena = new gridEntry[size];
}

void GameArenaScript::Update()
{}

void GameArenaScript::Render(const glm::vec3&) const
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
	const Point2i startPos{ ((width - totalWidthNeeded) / 2) + (offsetX/2), height - offsetY };
	Point2i currentPos{ startPos };

	for (int row = 0; row < m_BaseWidth; ++row)
	{
		for (int column = 0; column < m_BaseWidth; ++column)
		{
			if (!(column - row >= 0)) continue;
			DrawHex(pRenderer, currentPos, hexSize);
			currentPos.x += offsetX;
		}

		// row is done, reset x position
		currentPos.x = startPos.x + (offsetX/2)*(row+1);
		currentPos.y -= static_cast<int>(static_cast<float>(offsetY) * .75f);
	}
}

Point2i GameArenaScript::GetHexPoint(Point2i center, float size, int i) const
{
	const float angle_deg = 60.f * static_cast<float>(i) - 30.f;
	const float angle_rad = static_cast<float>(M_PI) * angle_deg / 180.f;

	const int posX{ static_cast<int>(static_cast<float>(center.x) + size * cos(angle_rad)) };
	const int posY{ static_cast<int>(static_cast<float>(center.y) + size * sin(angle_rad)) };

	return { posX, posY };
}

void GameArenaScript::DrawHex(SDL_Renderer* /*pRenderer*/, Point2i center, float size) const
{
	//std::vector<Point2i> points{};
	//points.reserve(m_BaseWidth);
	//for (int i = 0; i < m_BaseWidth; ++i)
	//{
	//	points.push_back(GetHexPoint(center, size, i));
	//}

	// Calculate the top polygon points
	std::vector<Point2i> topPoints{};
	topPoints.reserve(4);
	topPoints.push_back(GetHexPoint(center, size, 5));
	topPoints.push_back(GetHexPoint(center, size, 0));
	topPoints.push_back(center);
	topPoints.push_back(GetHexPoint(center, size, 4));
	//DrawFilledPolygon(topPoints, m_InactiveHexColor, pRenderer);
	minigen::Renderer::GetInstance().RenderPolygon(topPoints, Color3f{1, 0, 0});

	// Calculate the right polygon points
	std::vector<Point2i> rightPoints{};
	rightPoints.reserve(4);
	rightPoints.push_back(GetHexPoint(center, size, 0));
	rightPoints.push_back(GetHexPoint(center, size, 1));
	rightPoints.push_back(GetHexPoint(center, size, 2));
	rightPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(rightPoints, Color3f{0, 0, 1});
	// Calculate the left polygon points
	std::vector<Point2i> leftPoints{};
	leftPoints.reserve(4);
	leftPoints.push_back(GetHexPoint(center, size, 2));
	leftPoints.push_back(GetHexPoint(center, size, 3));
	leftPoints.push_back(GetHexPoint(center, size, 4));
	leftPoints.push_back(center);
	minigen::Renderer::GetInstance().RenderPolygon(leftPoints, Color3f{0, 1, 0});


	//// Set correct draw color
	//SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);

	//const PolygonShape rightPolygon{ rightPoints };
	//const PolygonShape leftPolygon{ leftPoints };
	//
	//result = DrawFilledPolygon(rightPolygon, m_InactiveHexColor, pRenderer);
	//result = DrawFilledPolygon(leftPolygon, m_InactiveHexColor, pRenderer);

	//// Draw outer lines
	//for (int i = 0; i < m_BaseWidth; ++i)
	//{
	//	const int nextIndex = (i + 1) % m_BaseWidth;
	//	SDL_RenderDrawLine(pRenderer, points[i].x, points[i].y, points[nextIndex].x, points[nextIndex].y);
	//}


	//// Draw inner lines from center
	//SDL_RenderDrawLine(pRenderer, center.x, center.y, points[0].x, points[0].y); // Center to top right
	//SDL_RenderDrawLine(pRenderer, center.x, center.y, points[2].x, points[2].y); // Center to bottom
	//SDL_RenderDrawLine(pRenderer, center.x, center.y, points[4].x, points[4].y); // Center to top left
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
