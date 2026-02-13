#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Game game;
	if (game.Initialize())
	{
		game.GameLoop();
	}
	game.Finalize();

	return 0;
}
