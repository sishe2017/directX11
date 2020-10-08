#include "Mouse.h"
#include "Log.h"

using namespace std;

//初始化静态变量
Vector2 Mouse::mousePosition;

//鼠标有键按下
bool Mouse::GetMouseButtonDown(MouseButton mouseButton)
{
    //如果鼠标对应按键处于按下状态，并且有键按下的事件发生,返回true
    if (GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == true &&
        GetInstance().keyDownEvents[static_cast<unsigned int>(mouseButton)] == true)
    {
        GetInstance().keyDownEvents[static_cast<unsigned int>(mouseButton)] = false;
        return true;
    }

    return false;
}

//鼠标有键输入
bool Mouse::GetMouseButton(MouseButton mouseButton)
{
    return GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == true;
}

//鼠标有键弹起
bool Mouse::GetMouseButtonUp(MouseButton mouseButton)
{
    //如果鼠标对应按键处于按下状态，并且有键弹起的事件发生,返回true
    if (GetInstance().keyStates[static_cast<unsigned int>(mouseButton)] == false &&
        GetInstance().keyUpEvents[static_cast<unsigned int>(mouseButton)] == true)
    {
        GetInstance().keyUpEvents[static_cast<unsigned int>(mouseButton)] = false;
        return true;
    }

    return false;
}

Mouse& Mouse::GetInstance()
{
    static Mouse mouse;
    return mouse;
}

//当键盘有键落下的事件处理
void Mouse::OnKeyDown(unsigned int keycode)
{
    //设置鼠标键位和键落下事件标志
    GetInstance().keyStates[keycode] = true;
    GetInstance().keyDownEvents[keycode] = true;
}

//当键盘有键弹起的事件处理
void Mouse::OnKeyUp(unsigned int keycode)
{
    //设置鼠标键位和键落下事件标志
    GetInstance().keyStates[keycode] = false;
    GetInstance().keyUpEvents[keycode] = true;
}

//鼠标移动的事件处理
void Mouse::OnMouseMove(int x, int y)
{
    //更新鼠标位置
    GetInstance().mousePosition.x = static_cast<float>(x);
    GetInstance().mousePosition.y = static_cast<float>(y);
}
