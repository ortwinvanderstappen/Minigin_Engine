#pragma once
namespace minigen {
	class GameObject;
}

class Observer
{
public:
	enum class Event
	{
		event_player_die,
		event_player_lose_life
	};

	virtual ~Observer() = default;
	virtual void Notify(const minigen::GameObject&, Event event) = 0;

protected:
	Observer() = default;
};

