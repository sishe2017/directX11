#pragma once
#include <string>
#include <Windows.h>
#include "Window/Window.h"
#include "Time.h"
#include "DirectX11.h"
#include <memory>
#include <vector>
#include "GameObject.h"

//�����࣬��Ϸ�߼���Ҫ�̳������
class ShadowEngine
{
public:
	//������Ϸ
	void Run();

	//�����Ϸ����
	static void AddGameObject(std::shared_ptr<GameObject> gameObject);
	//������Ϸ
	static void RunGame();

private:
	//����ģʽ
	ShadowEngine();
	ShadowEngine(const ShadowEngine&) = delete;
	ShadowEngine& operator=(const ShadowEngine&) = delete;
	static ShadowEngine& GetInstance();

	//�����ı༭
	void EditScene();
	//����ÿ����Ϸ����һ��ʼ����Ϸ�߼�
	void Start();
	//����ÿ����Ϸ����ÿһ֡����Ϸ�߼�
	void Update();
	//��Ϸ���弯��
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};
