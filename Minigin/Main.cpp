#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

// Github repo: https://github.com/ortwinvanderstappen/Minigin_Engine

int main(int, char* [])
{
	minigen::Minigin engine;
	engine.Run();
	return 0;
}