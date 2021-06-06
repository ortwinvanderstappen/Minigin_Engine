#pragma once
#include <memory>
#include <Singleton.h>

class ScoreObserver;

class GameContext : public minigen::Singleton<GameContext>
{
public:
	void SetScoreObserver(const std::shared_ptr<ScoreObserver>& spScoreObserver);
	const std::shared_ptr<ScoreObserver>& GetScoreObserver() const;
private:
	std::shared_ptr<ScoreObserver> m_spScoreObserver;
};

