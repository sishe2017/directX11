#include <Windows.h>
#include <string>
#include "ShadowEngine.h"

using namespace std;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, PSTR szCmdLine, int iCmdShow)
{
	//������Ϸ
	ShadowEngine::RunGame();

	return 0;
}