#include "stdafx.h"
#include "GameContext.h"

void GameContext::SetScoreObserver(const std::shared_ptr<ScoreObserver>& spScoreObserver)
{
	m_spScoreObserver = spScoreObserver;
}

const std::shared_ptr<ScoreObserver>& GameContext::GetScoreObserver() const
{
	return m_spScoreObserver;
}
