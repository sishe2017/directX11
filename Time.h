#pragma once
#include <chrono>

//时间类
class Time
{
	friend class ShadowEngine;
public:
	//相邻两帧间隔的时间
	static float deltaTime;

private:
	//单例模式
	Time();
	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	static Time& GetInstance();

	//上一帧的时间
	std::chrono::steady_clock::time_point lastFrameTime;

	//更新deltaTime的值
	static void UpdateDeltaTime();
};

