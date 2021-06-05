#include "CompletedTilesObserver.h"

#include "GameArena.h"

CompletedTilesObserver::CompletedTilesObserver(GameArena* pArena) :
	m_pArena(pArena),
	m_TotalTiles(0),
	m_CompletedTiles(0)
{}

void CompletedTilesObserver::Notify(minigen::GameObject*, Event event)
{
	switch (event)
	{
	case Event::event_tile_complete:
		m_CompletedTiles++;
		CheckArenaCompletion();
		break;
	case Event::event_tile_uncomplete:
		m_CompletedTiles--;
		CheckArenaCompletion();
		break;
	default:;
	}
}

void CompletedTilesObserver::SetTileCount(int tileCount)
{
	m_TotalTiles = tileCount;
}

int CompletedTilesObserver::GetCompletedTileCount() const
{
	return m_CompletedTiles;
}

void CompletedTilesObserver::CheckArenaCompletion() const
{
	if (m_CompletedTiles == m_TotalTiles)
	{
		m_pArena->HandleLevelCompletion();
	}
}
