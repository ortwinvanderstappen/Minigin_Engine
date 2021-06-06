#pragma once
#include "stdafx.h"

#include <Observer.h>

class ScoreObserver : public minigen::Observer
{
public:
	ScoreObserver();
	
	void Notify(minigen::GameObject* pGameObject, Event event) override;
	int GetScore() const;
	void ResetScore();

private:
	int m_Score;
};

