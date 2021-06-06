// Github repo: https://github.com/ortwinvanderstappen/Minigin_Engine
#include "stdafx.h"
#include <iostream>

#include "Game.h"

int main(int, char* [])
{
	std::cout << "Welcome to the game!\n";
	Game* pGame = new Game();
	pGame->Run();
	delete pGame;

	return 0;
}
