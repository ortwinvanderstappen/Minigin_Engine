#pragma once
#pragma warning (push)
#pragma warning(disable: 4201)
#include "RenderComponent.h"
#pragma warning(pop)
#include <SDL_render.h>
#include "structs.h"

struct gridEntry
{
	bool isActivated = false;
};

class GameArenaScript : public minigen::RenderComponent
{
public:
	GameArenaScript(int baseWidth);
	~GameArenaScript() override;

	void Initialize();
	
	void Update() override;
	void Render(const glm::vec3& positionOffset) const override;
private:
	Point2i GetHexPoint(Point2i center, float size, int i) const;
	void DrawHex(SDL_Renderer* pRenderer, Point2i center, float size) const;
	int CalculateArenaHexCount () const;
	
	int m_BaseWidth = -1;
	gridEntry* pArena = nullptr;

	SDL_Color m_InactiveHexColor{255,255,255,255};
	SDL_Color m_ActiveHexColor{255,255,0,255};
	SDL_Color m_LeftSideColor{255,0,0,255};
	SDL_Color m_RightSideColor{0,0,255,255};
	
};
