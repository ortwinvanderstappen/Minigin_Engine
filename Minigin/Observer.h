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
			event_collision,
			mouse_click,
			event_qbert_death,
			event_tile_color_change,
			event_coily_fall,
			event_stage_complete,
			event_slick_sam_caught,
			event_tile_complete,
			event_tile_uncomplete,
			event_remaining_flying_disc,
			event_coily_transform
		};

		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
		
		virtual void Notify(GameObject* pGameObject, Event event) = 0;

	protected:
		Observer() = default;
	};
}

