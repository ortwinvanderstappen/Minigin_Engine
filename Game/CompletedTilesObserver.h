#pragma once
#include "stdafx.h"

#include <Observer.h>

class GameArena;

class CompletedTilesObserver : public minigen::Observer
{
public:
	CompletedTilesObserver(GameArena* pArena);

	void Notify(minigen::GameObject* pGameObject, Event event) override;

	void SetTileCount(int tileCount);
	int GetCompletedTileCount() const;

private:
	void CheckArenaCompletion() const;

	GameArena* m_pArena;
	int m_TotalTiles;
	int m_CompletedTiles;
};

