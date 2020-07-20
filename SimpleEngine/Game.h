#pragma once
#include "ShadowEngine.h"
#include <memory>

//游戏，具体的游戏逻辑在这里书写
class Game : ShadowEngine
{
public:
	Game(HINSTANCE hInstance);

	//运行游戏
	void Run();

private:
	
};

