#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR cmdLine, int showCmd)
{
	//������Ϸ
	Game game(hInstance);
	game.Run();

	return 0;
}