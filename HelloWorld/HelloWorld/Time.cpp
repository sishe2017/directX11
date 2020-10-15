#include "Time.h"


//初始化静态变量
float Time::deltaTime = 0;

using namespace std;

Time::Time()
{
    lastFrameTime = chrono::steady_clock::now();
}

Time& Time::GetInstance()
{
    static Time time;
    return time;
}

//更新deltaTime的值
void Time::UpdateDeltaTime()
{
    auto tmp = GetInstance().lastFrameTime;
    GetInstance().lastFrameTime = chrono::steady_clock::now();
    deltaTime = static_cast<chrono::duration<float>>(GetInstance().lastFrameTime - tmp).count();
}
