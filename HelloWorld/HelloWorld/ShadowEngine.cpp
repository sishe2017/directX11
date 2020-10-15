#include "ShadowEngine.h"
#include "Component/ScriptBase.h"
#include "Scripts/CubeBehavior.h"
#include <iostream>
#include "Random.h"

using namespace std;

ShadowEngine::ShadowEngine()
{
	int width = 800;
	int height = 600;
	//创建一个窗口
	Window window(width, height, L"Hello World");
	//初始化DirectX11
	DirectX11::Init(window.hwnd, 800, 600);
}

ShadowEngine& ShadowEngine::GetInstance()
{
	static ShadowEngine shadowEngine;
	return shadowEngine;
}

//运行游戏
void ShadowEngine::Run()
{
	//一开始需要调用的逻辑代码
	Start();
	//消息循环
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		//如果从消息队列中取到了消息
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//翻译消息
			TranslateMessage(&msg);
			//将键盘消息翻译成字符消息
			DispatchMessage(&msg);
		}

		//更新每帧间隔时间
		Time::UpdateDeltaTime();
		//每帧调用的逻辑代码
		Update();
	}
}

//添加游戏物体
void ShadowEngine::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	GetInstance().gameObjects.push_back(gameObject);
}

void ShadowEngine::RunGame()
{
	GetInstance().Run();
}

void ShadowEngine::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		for (int j = 0; j < gameObjects[i]->components.size(); j++)
		{
			auto tmp = dynamic_pointer_cast<ScriptBase>(gameObjects[i]->components[j]);
			if (tmp != nullptr)
			{
				tmp->Update();
			}
		}
		//绘制游戏物体
		gameObjects[i]->Draw();
	}
	//输出到屏幕
	DirectX11::OutputToScreen();
}

//场景的编辑
void ShadowEngine::EditScene()
{
	for (int i = 0; i < 7; i++)
	{
		//todo：游戏一开始物体的设置：
		auto cube = GameObject::CreatePrimitive(PrimitiveType::Cube);
		//记录生成的游戏物体
		AddGameObject(cube);
		//设置物体位置
		auto x = Random::RangeFloat(-5, 5);
		auto y = Random::RangeFloat(-5, 5);
		auto z = Random::RangeFloat(8, 15);
		cube->transform->SetPosition(Vector3(x, y, z));
		//给cube添加脚本
		cube->AddComponent(make_shared<CubeBehavior>());
	}
}

//游戏一开始要进行的一些操作
void ShadowEngine::Start()
{
	//编辑场景
	EditScene();

	//调用游戏物体脚本的Start函数
	for (int i = 0; i < gameObjects.size(); i++)
	{
		for (int j = 0; j < gameObjects[i]->components.size(); j++)
		{
			auto tmp = dynamic_pointer_cast<ScriptBase>(gameObjects[i]->components[j]);
			if (tmp != nullptr)
			{
				tmp->Start();
			}
		}
	}
}



