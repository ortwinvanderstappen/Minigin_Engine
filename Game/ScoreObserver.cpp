#include "ScoreObserver.h"

void ScoreObserver::Notify(minigen::GameObject*, Event event)
{
	switch(event)
	{
	case Event::event_tile_color_change: 
		m_Score += 25;
		break;
	case Event::event_coily_fall: 
		m_Score += 500;
		break;
	case Event::event_stage_complete: 
		// TODO: check how many flying discs are left...
		break;
	case Event::event_slick_sam_caught: 
		m_Score += 300;
		break;
	default: ;
	}
}

int ScoreObserver::GetScore() const
{
	return m_Score;
}

void ScoreObserver::ResetScore()
{
	m_Score = 0;
}
