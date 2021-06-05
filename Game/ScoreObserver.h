#pragma once
#include <Observer.h>

#include "RenderComponent.h"

class ScoreObserver : public minigen::Observer
{
public:
	void Notify(minigen::GameObject* pGameObject, Event event) override;
	int GetScore() const;
	void ResetScore();

private:
	int m_Score;
};

