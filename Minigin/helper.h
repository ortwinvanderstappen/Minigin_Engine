#pragma once
#include <SDL_render.h>
#include "structs.h"
#include "Renderer.h"

void DrawFilledPolygon(const std::vector<Point2i>& polyPoints, const SDL_Color& color, SDL_Renderer* pRenderer);