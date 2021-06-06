#pragma once
#include <memory>
#include <vector>
#include <Windows.h>

struct SDL_Window;
namespace minigen
{
	class GameObject;
	class Minigin
	{
	public:
		void Initialize();
		void Run();
	private:
		void Cleanup();
		
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		bool m_IsInitialized = false;

		std::vector<std::shared_ptr<GameObject>> m_Players{};
	};
}