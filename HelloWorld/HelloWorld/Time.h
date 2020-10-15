#pragma once
#include <chrono>

//ʱ����
class Time
{
	friend class ShadowEngine;
public:
	//������֡�����ʱ��
	static float deltaTime;

private:
	//����ģʽ
	Time();
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	static Time& GetInstance();

	//��һ֡��ʱ��
	std::chrono::steady_clock::time_point lastFrameTime;

	//����deltaTime��ֵ
	static void UpdateDeltaTime();
};

