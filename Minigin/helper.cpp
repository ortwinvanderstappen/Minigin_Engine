#include "MiniginPCH.h"
#include "helper.h"

// https://www.youtube.com/watch?v=Xw7x4m_SR6s
void DrawFilledPolygon(const std::vector<Point2i>& polyPoints, const SDL_Color& color, SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a);
	
	int minX = INT_MAX; int maxX = -INT_MAX;
	int minY = INT_MAX; int maxY = -INT_MAX;

	for (const Point2i& p : polyPoints)
	{
		if (p.x < minX) minX = p.x;
		if (p.x > maxX) maxX = p.x;

		if (p.y < minY) minY = p.y;
		if (p.y > maxY) maxY = p.y;
	}

	// Make a bounding box that's slightly larger than the polygon
	minX--; minY--;
	maxX++; maxY++;
	const Recti boundingRect{ minX, minY, (maxX - minX), (maxY - minY) };

	// Draw the actual polygon
	int x1, y1;
	int x2, y2;
	int edgeStartX, edgeStartY;
	int edgeEndX, edgeEndY;
	int detA;
	const int n = static_cast<int>(polyPoints.size());
	float u, v;

	for (int x = 0; x < boundingRect.w; ++x)
	{
		for (int y = 0; y < boundingRect.y; ++y)
		{
			int count = 0;
			// For every point in the polygon, check the intersection count
			for (int i = 0; i < n; ++i)
			{
				// Form the vertices for the search line
				x1 = x + boundingRect.x;				y1 = y + boundingRect.y;
				x2 = boundingRect.w + boundingRect.x;	y2 = boundingRect.h + boundingRect.y;

				// Extract the two vertices for this edge
				edgeStartX = polyPoints[i].x;			edgeStartY = polyPoints[i].y;
				edgeEndX = polyPoints[(i + 1) % n].x;	edgeEndY = polyPoints[(i + 1) % n].y;

				// Check for an intersection between the search line and this edge
				// Compute the determinant
				detA = (x1 - x2) * (edgeEndY - edgeStartY) - (edgeEndX - edgeStartX) * (y1 - y2);

				// If this is zero, then there is no intersection
				if (detA != 0)
				{
					u = static_cast<float>((edgeEndY - edgeStartY) * (x1 - edgeStartX) + (edgeStartX - edgeEndX) * (y1 - edgeStartY)) / static_cast<float>(detA);
					v = static_cast<float>((y2 - y1) * (x1 - edgeStartX) + (x1 - x2) * (y1 - edgeStartY)) / static_cast<float>(detA);

					// If u and v are both between zero and one then we have a valid intersection
					if ((u >= 0.0f) && (u <= 1.0f) && (v >= 0.0f) && (v <= 1.0f))
					{
						count++;
					}
				}
			}
			
			// If count is odd, set the pixel
			if (count % 2)
			{
				SDL_RenderDrawPoint(pRenderer, boundingRect.x + x, boundingRect.y + y);
			}
		}
	}
}
