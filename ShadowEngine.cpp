#include "ShadowEngine.h"
#include "ScriptBase.h"
#include "CubeBehavior.h"
#include <iostream>

using namespace std;

ShadowEngine::ShadowEngine()
{
	int width = 800;
	int height = 600;
	//����һ������
	Window window(width, height, L"Hello World");
	//��ʼ��DirectX11
	DirectX11::Init(window.hwnd, 800, 600);
}

ShadowEngine& ShadowEngine::GetInstance()
{
	static ShadowEngine shadowEngine;
	return shadowEngine;
}

//������Ϸ
void ShadowEngine::Run()
{
	//һ��ʼ��Ҫ���õ��߼�����
	Start();
	//��Ϣѭ��
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	while (msg.message != WM_QUIT)
	{
		//�������Ϣ������ȡ������Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			//������Ϣ
			TranslateMessage(&msg);
			//��������Ϣ������ַ���Ϣ
			DispatchMessage(&msg);
		}

		//����ÿ֡���ʱ��
		Time::UpdateDeltaTime();
		//ÿ֡���õ��߼�����
		Update();
	}
}

//�����Ϸ����
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
	
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	for (int j = 0; j < gameObjects[i]->components.size(); j++)
	//	{
	//		auto tmp = dynamic_pointer_cast<ScriptBase>(gameObjects[i]->components[j]);
	//		if (tmp != nullptr)
	//		{
	//			tmp->Update();
	//		}
	//	}
	//			
	//	//������Ϸ����
	//	gameObjects[i]->Draw();
	//}

	DirectX11::DrawTriangle();

	////��������
	//DirectX11::Draw();
	//�������Ļ
	DirectX11::OutputToScreen();

	
}

//��Ϸһ��ʼҪ���е�һЩ����
void ShadowEngine::Start()
{
	//todo����Ϸһ��ʼ��������ã�
	auto cube = GameObject::CreatePrimitive(PrimitiveType::Cube);
	//��������λ��
	cube->transform->SetPosition(Vector3(0, 0, 8.0f));
	//��cube��ӽű�
	cube->AddComponent(make_shared<CubeBehavior>());

	//������Ϸ����ű���Start����
	for (int i = 0; i < gameObjects.size(); i++)
		for (int j = 0; j < gameObjects[i]->components.size(); j++)
		{
			auto tmp = dynamic_pointer_cast<ScriptBase>(gameObjects[i]->components[j]);
			if (tmp != nullptr)
			{
				tmp->Start();
			}
		}

	//��¼���ɵ���Ϸ����
	AddGameObject(cube);

	//DirectX11::PrepareDrawTriangle(0, 8.0f);
}



