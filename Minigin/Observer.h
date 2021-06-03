#pragma once

namespace minigen {
	class GameObject;
	class Observer
	{
	public:
		enum class Event
		{
			event_player_die,
			event_player_lose_life,
			event_collision
		};

		virtual ~Observer() = default;
		virtual void Notify(GameObject* pGameObject, Event event) = 0;

	protected:
		Observer() = default;
	};
}

