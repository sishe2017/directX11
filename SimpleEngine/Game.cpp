#include "Game.h"

using namespace std;

Game::Game(HINSTANCE hInstance):
	ShadowEngine(hInstance, L"initial", 800, 600)
{
	Init();
}

void Game::Run()
{
	ShadowEngine::Run();
}
