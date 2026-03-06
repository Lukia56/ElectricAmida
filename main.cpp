#include "Game.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

bool Game::isRunning = true;

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
