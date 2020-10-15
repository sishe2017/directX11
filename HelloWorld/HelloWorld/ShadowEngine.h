#pragma once
#include <string>
#include <Windows.h>
#include "Window/Window.h"
#include "Time.h"
#include "DirectX11.h"
#include <memory>
#include <vector>
#include "GameObject.h"

//引擎类，游戏逻辑需要继承这个类
class ShadowEngine
{
public:
	//运行游戏
	void Run();

	//添加游戏物体
	static void AddGameObject(std::shared_ptr<GameObject> gameObject);
	//运行游戏
	static void RunGame();

private:
	//单例模式
	ShadowEngine();
	ShadowEngine(const ShadowEngine&) = delete;
	ShadowEngine& operator=(const ShadowEngine&) = delete;
	static ShadowEngine& GetInstance();

	//场景的编辑
	void EditScene();
	//调用每个游戏物体一开始的游戏逻辑
	void Start();
	//调用每个游戏物体每一帧的游戏逻辑
	void Update();
	//游戏物体集合
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};
